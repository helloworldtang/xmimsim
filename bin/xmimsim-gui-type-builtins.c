


#include "xmimsim-gui-type-builtins.h"
#include "xmimsim-gui-compound-dialog.h"
#include "xmimsim-gui-layer-dialog.h"
#include "xmimsim-gui-discrete-energy-dialog.h"
#include "xmimsim-gui-continuous-energy-dialog.h"

/* enumerations from "xmimsim-gui-compound-dialog.h" */
GType
xmi_msim_gui_compound_dialog_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { XMI_MSIM_GUI_COMPOUND_DIALOG_ADD, "XMI_MSIM_GUI_COMPOUND_DIALOG_ADD", "add" },
      { XMI_MSIM_GUI_COMPOUND_DIALOG_EDIT, "XMI_MSIM_GUI_COMPOUND_DIALOG_EDIT", "edit" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static(g_intern_static_string("XmiMsimGuiCompoundDialogType"), values);
  }
  return etype;
}

/* enumerations from "xmimsim-gui-layer-dialog.h" */
GType
xmi_msim_gui_layer_dialog_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { XMI_MSIM_GUI_LAYER_DIALOG_ADD, "XMI_MSIM_GUI_LAYER_DIALOG_ADD", "add" },
      { XMI_MSIM_GUI_LAYER_DIALOG_EDIT, "XMI_MSIM_GUI_LAYER_DIALOG_EDIT", "edit" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static(g_intern_static_string("XmiMsimGuiLayerDialogType"), values);
  }
  return etype;
}

/* enumerations from "xmimsim-gui-discrete-energy-dialog.h" */
GType
xmi_msim_gui_discrete_energy_dialog_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { XMI_MSIM_GUI_DISCRETE_ENERGY_DIALOG_ADD, "XMI_MSIM_GUI_DISCRETE_ENERGY_DIALOG_ADD", "add" },
      { XMI_MSIM_GUI_DISCRETE_ENERGY_DIALOG_EDIT, "XMI_MSIM_GUI_DISCRETE_ENERGY_DIALOG_EDIT", "edit" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static(g_intern_static_string("XmiMsimGuiDiscreteEnergyDialogType"), values);
  }
  return etype;
}

/* enumerations from "xmimsim-gui-continuous-energy-dialog.h" */
GType
xmi_msim_gui_continuous_energy_dialog_type_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { XMI_MSIM_GUI_CONTINUOUS_ENERGY_DIALOG_ADD, "XMI_MSIM_GUI_CONTINUOUS_ENERGY_DIALOG_ADD", "add" },
      { XMI_MSIM_GUI_CONTINUOUS_ENERGY_DIALOG_EDIT, "XMI_MSIM_GUI_CONTINUOUS_ENERGY_DIALOG_EDIT", "edit" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static(g_intern_static_string("XmiMsimGuiContinuousEnergyDialogType"), values);
  }
  return etype;
}



