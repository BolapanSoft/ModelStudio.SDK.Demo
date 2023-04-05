using mstudioData.sdk.net48.demo;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ModelStudioSDK.TestLaunch {
    public class Program {
        public static void Main(string[] args) {
            FactoryInterface factory = new FactoryInterface();
            factory.GetApiVersion();
            factory.GetMainAppKey();
        }
    }
}
