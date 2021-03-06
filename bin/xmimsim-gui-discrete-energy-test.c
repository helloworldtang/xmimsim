/*
Copyright (C) 2017 Tom Schoonjans and Laszlo Vincze

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "xmimsim-gui-discrete-energy-dialog.h"
#include "xmi_data_structs.h"

#include <stdio.h>

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv);

	GtkWidget *dialog = xmi_msim_gui_discrete_energy_dialog_new(NULL, XMI_MSIM_GUI_DISCRETE_ENERGY_DIALOG_EDIT);

	struct xmi_energy_discrete orig = {
		.energy = 1.0,
		.horizontal_intensity = 2.0,
		.vertical_intensity = 3.0,
		.sigma_x = 4.0,
		.sigma_y = 5.0,
		.sigma_xp = 6.0,
		.sigma_yp = 7.0,
		.distribution_type = 0,
		.scale_parameter = 8.0
	};
	xmi_msim_gui_discrete_energy_dialog_set_discrete_energy(XMI_MSIM_GUI_DISCRETE_ENERGY_DIALOG(dialog), &orig);

	fprintf(stderr, "Before gtk_dialog_run\n");
	int rv = gtk_dialog_run(GTK_DIALOG(dialog));

	if (rv == GTK_RESPONSE_ACCEPT) {
		//something was changed
		struct xmi_energy_discrete *disc = xmi_msim_gui_discrete_energy_dialog_get_discrete_energy(XMI_MSIM_GUI_DISCRETE_ENERGY_DIALOG(dialog));
		fprintf(stdout, "Energy: %g\n", disc->energy);
		fprintf(stdout, "Horizontal intensity: %g\n", disc->horizontal_intensity);
		fprintf(stdout, "Vertical intensity: %g\n", disc->vertical_intensity);
		fprintf(stdout, "sigma_x: %g\n", disc->sigma_x);
		fprintf(stdout, "sigma_xp: %g\n", disc->sigma_xp);
		fprintf(stdout, "sigma_y: %g\n", disc->sigma_y);
		fprintf(stdout, "sigma_yp: %g\n", disc->sigma_yp);
		fprintf(stdout, "distribution_type: %i\n", disc->distribution_type);
		if (disc->distribution_type != XMI_DISCRETE_MONOCHROMATIC)
			fprintf(stdout, "scale_parameter: %g\n", disc->scale_parameter);
		g_free(disc);
	}
	gtk_widget_destroy(dialog);
	return 0;	
}

