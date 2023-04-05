using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using mstudioDatasdk;
using System.ComponentModel.Design;

namespace mstudioData.sdk.net48.demo {
    [TestClass]
    public class FactoryInterface {
        [TestMethod]
        public void GetApiVersion() {
            var fi = new Factory();
            fi.GetApiVersion(out int majorVer, out int minorVer);
            Assert.IsTrue(majorVer > 0);
            Assert.IsTrue(minorVer > 0);
        }
    }
}
