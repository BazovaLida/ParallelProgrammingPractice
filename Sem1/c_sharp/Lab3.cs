using System;
using System.Linq;
using System.Threading;

namespace Parallel_Programing_c_sharp
{
    internal class Lab3
    {
        private static readonly Data.Data Data = new Data.Data(10);
        const int c = 1;

        public static void Main(string[] args)
        {
            Console.WriteLine("The program is started");
            var thread1 = new Thread (Func1);          // Kick off all threads
            var thread2 = new Thread (Func2);
            var thread3 = new Thread (Func3);

            thread1.Name = "Thread for function 1";
            thread2.Name = "Thread for function 2";
            thread3.Name = "Thread for function 3";
            
            //enum ThreadPriority { Lowest, BelowNormal, Normal, AboveNormal, Highest }
            thread1.Priority = ThreadPriority.AboveNormal;
            thread2.Priority = ThreadPriority.BelowNormal;
            thread3.Priority = ThreadPriority.Normal;
            
            thread1.Start();                               // running Thread1()
            thread2.Start();                               // running Thread2()
            thread3.Start();                               // running Thread3()
            
            thread1.Join();
            thread2.Join();
            thread3.Join();

            Console.WriteLine("\nThread with main function is finished");
        }
        
        //F1: d = (A * ((B + C) * (MA * ME)))
        private static void Func1()
        {
            Console.WriteLine("Thread 1 is started with name " + Thread.CurrentThread.Name +
                              ", priority "+ Thread.CurrentThread.Priority);

            Data.F1_input(c);
            Thread.Sleep(5000);
            Data.F1_calc();
            var d = Data.F1_result();
            Thread.Yield();
            Console.WriteLine("\nThread 1 is finished. Result: d = " + d);
        }
        
        //F2: MG = SORT(MF) * MK + ML
        private static void Func2()
        {
            Console.WriteLine("Thread 2 is started with name " + Thread.CurrentThread.Name +
                              ", priority "+ Thread.CurrentThread.Priority);

            
            Data.F2_input(c);
            Data.F2_calc();
            Thread.Sleep(1000);
            var MG = Data.F2_result();
            var stringResult = string.Join(",",
                Enumerable.Range(0, MG.GetUpperBound(0) + 1)
                    .Select(x => Enumerable.Range(0, MG.GetUpperBound(1) + 1)
                        .Select(y => MG[x, y]))
                    .Select(z => "{" + string.Join(",", z) + "}"));

            Console.WriteLine("\nThread 2 is finished. Result: MG = \n" + stringResult);
        }
        
        //F3: O = SORT(R + S) * (MT * MP)
        private static void Func3()
        {
            Console.WriteLine("Thread 3 is started with name " + Thread.CurrentThread.Name +
                              ", priority "+ Thread.CurrentThread.Priority);

            Data.F3_input(c);
            Thread.Yield();
            Data.F3_calc();
            var O = Data.F3_result();
            var stringResult = "{" + string.Join(", ", O) + "}";

            Console.WriteLine("\nThread 3 is finished. Result: O = \n" + stringResult);
        }
    }
}