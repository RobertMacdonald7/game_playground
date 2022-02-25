using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CubeApp.UserControls;

namespace CubeApp.ViewModel
{
    public class MainWindowViewModel
    {
        public ObservableCollection<ModularRectangle> Controls { get; set; }

        public MainWindowViewModel()
        {

        }
    }
}
