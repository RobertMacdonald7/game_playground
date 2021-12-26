using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace CubeApp.Converters
{
	internal class ControlSizeToFontSizeConverter: IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
		{
			var parsedValue = int.Parse(value.ToString()!);
			var parsedParameter = int.Parse(parameter.ToString()!);

			return (parsedValue / parsedParameter).ToString();
		}

		public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
		{
			var parsedValue = int.Parse(value.ToString()!);
			var parsedParameter = int.Parse(parameter.ToString()!);

			return (parsedValue * parsedParameter).ToString();
		}
	}
}
