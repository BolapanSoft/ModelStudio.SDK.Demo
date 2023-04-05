using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace ModelStudioSDK.Tests {
    internal class TestsHelper {
        public static class TestHelper {
            public static IEnumerable<MethodInfo> GetTests(Type testClass) {
                return testClass.GetMethods()
                    .Where(method => method.GetCustomAttributes(typeof(TestMethodAttribute), false).Any());
            }
        }
    }
}
