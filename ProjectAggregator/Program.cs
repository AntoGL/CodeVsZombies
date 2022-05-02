using System;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ProjectAggregator
{
    class Program
    {
        [STAThread]
        static void Main()
        {
            var aggregator = new ProjectAggregator();
            aggregator.AddDirectory(@"D:\Projects\CodeVsZombies\CodeVsZombies");

            var res = aggregator.Aggregate(@"main.cpp");

            Clipboard.SetText(res);
        }
    }
}
