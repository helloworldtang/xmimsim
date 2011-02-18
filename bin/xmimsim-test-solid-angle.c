#include "xmi_solid_angle.h"
#include "xmi_xml.h"
#include "xmi_random.h"


int main(int argc, char *argv[]) {
	int rv;
	xmi_inputFPtr inputFPtr;
	struct xmi_input *input;
	struct xmi_solid_angle *solid_angle;

	if (argc != 2)
		return 1;


	xmi_start_random_acquisition();


	rv = xmi_read_input_xml(argv[1],&input);

	if (rv != 1) {
		return 1;
	}

	//copy to the corresponding fortran variable
	xmi_input_C2F(input,&inputFPtr);
	//initialization
	if (xmi_init_input(&inputFPtr) == 0) {
		return 1;
	}

	xmi_solid_angle_calculation(inputFPtr, &solid_angle, argv[1]);

	//update hdf5 file
	if( xmi_update_solid_angle_hdf5_file(XMIMSIM_HDF5_SOLID_ANGLES, solid_angle) == 0)
		return 1;
	


	xmi_end_random_acquisition();

	return 0;
}
