using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace CubeApp.UserControls
{
	public enum ModularRectanglePosition
	{
		Center,
		Top,
		Bottom,
		Left,
		Right,
	}

	/// <summary>
	/// Interaction logic for ModularRectangle.xaml
	/// </summary>
	public partial class ModularRectangle : UserControl
	{
		public ModularRectanglePosition Position { get; set; } = ModularRectanglePosition.Center;

		public static readonly DependencyProperty NumberOfChildrenProperty = DependencyProperty.Register(
			"NumberOfChildren", typeof(int), typeof(ModularRectangle), new PropertyMetadata(new PropertyChangedCallback(NumberOfChildrenPropertyChanged)));

		public int NumberOfChildren
		{
			get => (int)GetValue(NumberOfChildrenProperty);
			set => SetValue(NumberOfChildrenProperty, value);
		}

		public int NumChild { get; set; }

		private static void NumberOfChildrenPropertyChanged(DependencyObject sender, DependencyPropertyChangedEventArgs e)
		{
			Console.WriteLine("NumberOfChildrenPropertyChanged");
		}

		private KeyValuePair<ModularRectanglePosition, ModularRectangle> _parent;
		public ObservableCollection<ModularRectangle> Children { get; set; }

		public ModularRectangle()
		{
			InitializeComponent();
		}
	}
}
