/**
 * Program      :   Dinning Philosophers Simulator
 * Author       :   Joaquim Costa
 * Date         :   November 24, 2011
 * Description  :   This program uses C# thread and monitor to implement the classic problem of the dinning philosophers
 * Class        :   CS435 Operating System
 */

using System;
using System.Threading;
using System.Timers;

namespace DinningPhilosophers
{
    class Philosopher
    {

        // static variables to be used throughout the program
        const int TOTAL_PHILOSOPHERS = 5;
        const int STARVATION_CHECK = 5000;  // 5 seconds
        const int ELAPSED_INTERVAL = 30000; // 30 seconds
        static readonly object _locker = new Object();
        static System.Timers.Timer _runTime = new System.Timers.Timer();
        static System.Timers.Timer _starvationCheck = new System.Timers.Timer(STARVATION_CHECK);

        // instance variables 
        private enum Status { THINKING, HUNGRY, EATING };

        // keep this arrays parallel
        private int[] _state;           // state of each philosopher
        private string[] _name;         // name of each philosopher 
        private int[] _totalEatTime;    // accumulates the total time each philosophers ate

        public Philosopher()
        {
            System.Console.Title = "Dinning Philosophers -- Joaquim Costa";
            System.Console.WriteLine("WELCOME TO THE DINNING PHILOSOPHERS SIMULATION");
            System.Console.WriteLine("Press ENTER to start the simulation");
            System.Console.ReadLine();

            // initialize all instance variables
            init();
        }


        // initialize instance variables
        private void init()
        {
            _state = new int[TOTAL_PHILOSOPHERS];
            _totalEatTime = new int[TOTAL_PHILOSOPHERS];
            _name = new String[] { "Joaquim", "Socratis", "Plato", "Aristotle", "Karl Marx" };

            //set up the timer
            _runTime.Interval = ELAPSED_INTERVAL; // 30 seconds
            _runTime.Enabled = true;
            _runTime.Elapsed += new ElapsedEventHandler(OnTimedEvent);  // this will trigger an event every 30 seconds

            // set up starvation check
            _starvationCheck.Enabled = true;
            _starvationCheck.Elapsed += new ElapsedEventHandler(feedStarvingPhiloEvent);



            // initialize all philosophers to thinking state
            for (int i = 0; i < TOTAL_PHILOSOPHERS; i++)
            {
                _state[i] = (int)Status.THINKING;
                _totalEatTime[i] = 0;
                this.thinking(i);
            }
        }


        /**
         * prints the philosopher thinking*/
        private void thinking(int philosId)
        {
            System.Console.WriteLine("{0,-10} is thinnking.", _name[philosId]);
        }

        /**
         * prints the philosopher eating and add eating time*/
        private void eating(int philosId)
        {
            System.Console.ForegroundColor = ConsoleColor.Green;
            System.Console.WriteLine("{0,-10} is eating.", _name[philosId]);
            System.Console.ResetColor();

            // accumulate total eating time
            _totalEatTime[philosId]++;
        }

        /**
         * prints the philosopher hungry*/
        private void hungry(int philosId)
        {
            System.Console.ForegroundColor = ConsoleColor.Red;
            System.Console.WriteLine("{0,-10} is hungry.", _name[philosId]);
            System.Console.ResetColor();
        }

        /**
         * prints when the philosopher pickup chopsticks*/
        private void printPickup(int philosId)
        {
            System.Console.WriteLine("{0,-10} pickup left & right chopstick.", _name[philosId]);
        }

        /**
         * prints when the philosopher putdown chopsticks*/
        private void printPutdown(int philosId)
        {
            System.Console.WriteLine("{0,-10} putdown the chopsticks.", _name[philosId]);
        }

        /**
         * The philosopher uses this method to putdown chopstick*/
        private void putdown(int philosId)
        {
            lock (_locker)
            {
                this.printPutdown(philosId);

                // set the philosopher state to thinking since he just ate
                _state[philosId] = (int)Status.THINKING;
                this.thinking(philosId);

                this.test((philosId + 4) % TOTAL_PHILOSOPHERS); // check left philos
                this.test((philosId + 1) % TOTAL_PHILOSOPHERS); // check right philos

            }
        }


        /**
         * The philosopher uses this method to pickup chopstick*/
        private void pickup(int philosId)
        {
            lock (_locker)
            {
                // set philosopher state to hungry since he tried to eat
                _state[philosId] = (int)Status.HUNGRY;
                this.hungry(philosId);
                this.test(philosId);

                Thread.Sleep(1000);
            }
        }



        /**
         * check if philosopher is hungry and attempt to feed him
         */
        private void test(int philosId)
        {
            //allow philosopher to eat if philosopher is hungry
            //the philosopher to the left/right are not eating
            if ((_state[(philosId + 4) % TOTAL_PHILOSOPHERS] != (int)Status.EATING) &&
                (_state[philosId] == (int)Status.HUNGRY &&
                (_state[(philosId + 1) % TOTAL_PHILOSOPHERS] != (int)Status.EATING)))
            {

                // set philosopher state to eating since he have both chopsticks
                _state[philosId] = (int)Status.EATING;
                this.printPickup(philosId);
                Thread.Sleep(1000);
                this.eating(philosId);
            }

        }


        /**
         * Display the total eating time for each philosophers*/
        public void stats()
        {
            // set up coloring
            System.Console.ForegroundColor = ConsoleColor.DarkYellow;

            // table header
            System.Console.WriteLine("\n{0}{1}", "Philosopher".PadRight(14), "Eat Total".PadLeft(10));
            for (int i = 0; i < TOTAL_PHILOSOPHERS; i++)
            {
                System.Console.WriteLine("{0}{1}", _name[i].PadRight(14,'.'), _totalEatTime[i].ToString().PadLeft(10, '.'));
            }
            System.Console.WriteLine();
            System.Console.ResetColor();
        }

        /**
         * this method handle the timer event when the interval has elapsed*/
        private void OnTimedEvent(object sender, EventArgs e)
        {
            this.stats();
        }

        /*
         * This event has been set up to trigger every STARVATION_CHECK (5 seconds)*/
        private void feedStarvingPhiloEvent(object sender, EventArgs e)
        {
            int minId = 0;
            int min = _totalEatTime[0];
            int max = _totalEatTime[0];

            for (int i = 0; i < TOTAL_PHILOSOPHERS; i++)
            {
                // assign min
                if (min > _totalEatTime[i])
                {
                    min = _totalEatTime[i];
                    minId = i;
                }

                // assign max
                if (max < _totalEatTime[i])
                    max = _totalEatTime[i];
            }

            // check if difference is greater than 2
            if ((max - min) > 2)
            {
                if (_state[minId] == (int)Status.THINKING)
                {
                    _state[minId] = (int) Status.HUNGRY;        // set starving phil to hungry
                    if(minId > 0) _state[minId - 1] = (int)Status.THINKING;   // set left philo to thinking
                    if(minId < TOTAL_PHILOSOPHERS-1 ) _state[minId + 1] = (int)Status.THINKING;   // set left righ to thinking
                   
                    this.test(minId);
                }
				else if(_state[minId] == (int)Status.HUNGRY )
				{
					if(minId > 0) _state[minId - 1] = (int)Status.THINKING;   // set left philo to thinking
                    if(minId < TOTAL_PHILOSOPHERS-1 ) _state[minId + 1] = (int)Status.THINKING;   // set left righ to thinking
                   
                    this.test(minId);
				}

            }
        }



        /**
         * this method runs the pickup and putdown method to simulate 
         * philosophers eating in a table.*/
        public void run(object philosId)
        {
            int id = (int) philosId;

            // run un infinite loop
            while (true)
            {
                Thread.Sleep(1000);
                this.pickup(id);
                Thread.Sleep(1000);
                this.putdown(id);
            }
        }


        static void Main(string[] args)
        {
            Philosopher philos = new Philosopher();
            Thread[] threads = new Thread[Philosopher.TOTAL_PHILOSOPHERS];

            // initialize all threads
            for (int i = 0; i < Philosopher.TOTAL_PHILOSOPHERS; i++)
            {
                threads[i] = new Thread(new ParameterizedThreadStart(philos.run));
                //System.Console.WriteLine("Debugging: THREAD {0} IS BEING CREATED\n", i);
            }

            // start all thread
            for (int i = 0; i < Philosopher.TOTAL_PHILOSOPHERS; i++)
            {
                try
                {
                   // System.Console.WriteLine("Debugging: THREAD {0} IS BEING STARTED\n", i);
                    threads[i].Start(i);    // pass the parameter to the run method
                }
                catch (ThreadStateException e)
                {
                    Console.WriteLine(e);  // Display text of exception
                }
                catch (ThreadInterruptedException e)
                {
                    Console.WriteLine(e);
                }
            }

            // join all thread
            for (int i = 0; i < Philosopher.TOTAL_PHILOSOPHERS; i++)
            {
                try
                {
                    //System.Console.WriteLine("Debugging: THREAD {0} IS BEING JOINED\n", i);
                    threads[i].Join();                   
                }
                catch (ThreadStateException e)
                {
                    Console.WriteLine(e);  // Display text of exception
                }
                catch (ThreadInterruptedException e)
                {
                    Console.WriteLine(e);
                }
            }

            System.Console.ReadKey();
        }
    }
}