using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace CubeApp
{
	public class TreedNode
	{
		public TreedNode Top;
		public TreedNode Bottom;
		public TreedNode Left;
		public TreedNode Right;
	}

	/// <summary>
	/// Interaction logic for MainWindow_Test1.xaml
	/// </summary>
	public partial class MainWindow_Test1 : Window
	{
		// Recursive method to traverse through the tree?
		// How to add controls to the view to represent the tree?
		private object root = new TreedNode()
		{
			Top = new TreedNode { },
			Bottom = new TreedNode { },
			Left = new TreedNode { },
			Right = new TreedNode
			{
				Right = new TreedNode
				{
					Right = new TreedNode { }
				}
			}
		};

		public MainWindow_Test1()
		{
			InitializeComponent();
		}
	}
}
