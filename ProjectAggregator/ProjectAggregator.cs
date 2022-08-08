using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace ProjectAggregator
{
    class ProjectAggregator
    {
        private readonly List<Regex> _skipString = new List<Regex>();
        private readonly List<DirectoryInfo> _useDirectories = new List<DirectoryInfo>();
        private readonly Stack<FileInfo> _fileStack = new Stack<FileInfo>();
        private readonly StringBuilder _stringBuilder = new StringBuilder();
        private readonly HashSet<string> _systemHeaders = new HashSet<string>();
        private readonly HashSet<string> _aggregatedFiles = new HashSet<string>();

        public ProjectAggregator()
        {
            _skipString.Add(new Regex("#include \"pch.h\""));
            _skipString.Add(new Regex("#pragma once"));
        }

        public string Aggregate(string mainFile)
        {
            AddAggregateFile(mainFile);

            while (_fileStack.Any())
            {
                var file = _fileStack.Pop();
                AggregateFile(file);
            }


            return GetResult();
        }

        private void AddAggregateFile(string fileName)
        {
            var fileInfo = FindFile(fileName);

            if (fileInfo == null)
                throw new Exception($"File not exist: {fileName}");

            _fileStack.Push(fileInfo);
        }

        private void AddSkipString(FileInfo file)
        {
            _skipString.Add(new Regex($"#include \"{file.Name}\""));
        }

        private void AggregateInclude(string line)
        {
            if (IsSystemHeaderInclude(line))
                AggregateSystemHeaderInclude(line);
            else
                AggregateLocalHeaderInclude(line);
        }

        private bool IsSystemHeaderInclude(string line)
        {
            return Regex.IsMatch(line, "#include <\\S*>");
        }

        private void AggregateSystemHeaderInclude(string line)
        {
            // "#include <iostream>" => "#include ", "iostream", ""
            // Да, стоит использовать регулярки или более разумное преобразование, но мне лень.
            var libName = line.Split('<', '>')[1];
            _systemHeaders.Add(libName);
            _skipString.Add(new Regex($"#include <{libName}>"));
        }

        private void AggregateLocalHeaderInclude(string line)
        {
            // "#include \"BaseDefenders.h\"" => "#include ", "BaseDefenders", "h", ""
            var headerName = line.Split('"', '.')[1];
            
            var headerFile = FindFile($"{headerName}.h");
            AggregateFile(headerFile);

            var sourceFile = FindFile($"{headerName}.cpp");
            if(sourceFile != null)
                AggregateFile(sourceFile);
        }

        private FileInfo FindFile(string fileName)
        {
            if (File.Exists(fileName))
                return new FileInfo(fileName);

            return _useDirectories.SelectMany(d => d.EnumerateFiles())
                .FirstOrDefault(f => f.Name == fileName);
        }

        private void AggregateFile(FileInfo file)
        {
            if (!file.Exists)
                throw new Exception($"File not exists: {file.FullName}");

            if (_aggregatedFiles.Contains(file.Name))
                return;

            AddSkipString(file);
            _aggregatedFiles.Add(file.Name);

            var reader = new StreamReader(file.OpenRead());
            while (!reader.EndOfStream)
            {
                var line = reader.ReadLine();
                if (line == null)
                    continue;

                if (_skipString.Any(r => r.IsMatch(line)))
                    continue;

                if (IsInclude(line))
                    AggregateInclude(line);
                else
                    _stringBuilder.AppendLine(line);
            }
        }
        
        private string GetResult()
        {
            var systemLibIncludes = AggregateSystemLibsInclude();
            var sourceCode = _stringBuilder.ToString();

            return $"{systemLibIncludes}\n{sourceCode}";
        }
        
        private string AggregateSystemLibsInclude()
        {
            var builder = new StringBuilder();
            foreach (var header in _systemHeaders)
            {
                builder.AppendLine($"#include <{header}>");
            }

            return builder.ToString();
        }

        private bool IsInclude(string line)
        {
            return Regex.IsMatch(line, "#include \\S*");
        }

        public void AddDirectory(string directoryPath)
        {
            if (!Directory.Exists(directoryPath))
                throw new Exception($"Directory not exist: {directoryPath}");

            _useDirectories.Add(new DirectoryInfo(directoryPath));
        }

        public void AddString(string str)
        {
            _stringBuilder.AppendLine(str);
        }
    }
}