using System;

namespace CounterTest
{
	public class Counter
	{
		private int _count;
		private string _name;

		public string Name
		{
			get
			{
				return _name;
			}
			set
			{
				_name = value;
			}
		}
	

		public Counter (string name)
		{
			_name = name;
			_count = 0;
		}

		public int Value {
			get 
			{
				return _count;
			}
		}
		
		public void Increment()
		{
			_count = _count + 1;
			//return _count;
		}

		public void Reset ()
		{
			_count = 0;
		}
		
	}
}

