/* Copyright (C) 2000, 2001 Stefan Buehler <sbuehler@uni-bremen.de>
                            Patrick Eriksson <patrick@rss.chalmers.se>

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA. */

/*!
  \file   workspace.cc
  \brief  Definition of function wsv_data.

  This file contains the function define_wsv_data, which
  sets the WSV group names and the lookup data for the WSVs.
  You have to edit this function whenever you add a new
  workspace variable. 

  \author Stefan Buehler
  \date   2000-06-10

  Removed the wsv pointers. They are now in a separate place.
  \author Stefan Buehler
  \date   2000-08-10 */

#include "arts.h"
#include "matpackI.h"
#include "array.h"
#include "auto_wsv_groups.h"
#include "wsv_aux.h"

/*! The lookup information for the workspace variables. */
Array<WsvRecord> wsv_data;

void define_wsv_data()
{

  //--------------------< Build the wsv data >--------------------
  // Initialize to empty, just in case.
  wsv_data.resize(0);


  //--------------------< Spectroscopy Stuff >--------------------
  //                     --------------------
  wsv_data.push_back
    (WsvRecord
     ("lines",
      "A list of spectral line data.", 
      ArrayOfLineRecord_));

  wsv_data.push_back
    (WsvRecord
     ("lines_per_tg",
      "A list of spectral line data for each tag.\n"
      "Dimensions: (tag_groups.nelem()) (# of lines for this tag)", 
      ArrayOfArrayOfLineRecord_));

  wsv_data.push_back
    (WsvRecord
     ("tgs",
      "This is an array of arrays of OneTag tag definitions.\n"
      "It defines the available tag groups for the calculation\n"
      "of absorption coefficients and weighting functions.\n"
      "Contrary to the original Bredbeck definition, tags within a\n"
      "group must belong to the same species, because one VMR profile\n"
      "is associated with each tag group.", 
      TagGroups_));

  wsv_data.push_back
    (WsvRecord
     ("wfs_tgs",
      "This is an array of arrays of tag group definitions.\n"
      "It defines the tag groups for the calculation of weighting\n"
      "functions. The selected tag groups must be a subgroup of the\n"
      "tag groups defined for the absorption coefficient calculation.", 
      TagGroups_));

  wsv_data.push_back
    (WsvRecord
     ("lineshape",
      "Lineshape specification: function, norm, cutoff. There is one entry for\n"
      "each abs_tag, not for each species. This means if you have several\n"
      "abs_tags for different isotopes or transitions of a species, you\n"
      "may use different lineshapes.",
      ArrayOfLineshapeSpec_));


  //--------------------< Continuum Stuff >--------------------
  //                     -----------------
  wsv_data.push_back
    (WsvRecord
     ("cont_description_names",
      "Continuum model names. This variable should contain a list of\n"
      "names of continuum models. Associated with this WSV is the WSV\n"
      "`cont_description_parameters' which should contain continuum\n"
      "parameters for each model. Allowed models currently are:\n\n"
      "H2O-ContStandardSelf: Self component of a simple empirical\n"
      "   continuum model a la Liebe/Rosenkranz. Needs two parameters.\n"
      "H2O-ContStandardForeign: Foreign component of a simple empirical\n"
      "   continuum model a la Liebe/Rosenkranz. Needs two parameters.",
      ArrayOfString_));

  wsv_data.push_back
    (WsvRecord
     ("cont_description_parameters",
      "Continuum model parameters. See the WSV `cont_description_names'\n"
      "for a detailed description of the allowed continuum models. There\n"
      "should be one parameter vector here for each entry in\n"
      "`cont_description_names'.",
      ArrayOfVector_));


  //--------------------< 1D Input Atmosphere Stuff >--------------------
  //                     ---------------------------
  wsv_data.push_back
    (WsvRecord
     ("raw_ptz",
      "Matrix has rows:\n"
      "1. Pressure in Pa\n"
      "2. Temperature in K\n"
      "3. Altitude in m", 
      Matrix_));

  wsv_data.push_back
    (WsvRecord
     ("raw_vmrs",
      "The individual VMR profiles. Each species VMR profile comes with a\n"
      "pressure profile. The different species can hence be on different\n"
      "grids.\n"
      "The matrix has rows:\n"
      "1. Pressure in Pa\n"
      "2. VMR profile (absolute number)\n"
      "The array dimension is determined by the number of tag groups.", 
      ArrayOfMatrix_));


  //--------------------< General Absorption Stuff >--------------------
  //                     --------------------------
  wsv_data.push_back
    (WsvRecord
     ("p_abs",
      "The pressure grid for the absorption coefficients [Pa]. This\n"
      "is the basic independent grid for the absorption calculation, both\n"
      "in the 1D and 2D case. Therefore it remains a vector, even in 2D.\n"
      "The \"raw\" atmospheric data shall be interpolated to p_abs before\n"
      "the absorption calculations starts.",
      Vector_));
  
  wsv_data.push_back
    (WsvRecord
     ("f_mono",
      "The monochromatic frequency grid [Hz]. This grid is used when\n"
      "calculating absorption and pencil b",
      Vector_));
    

  //--------------------< 1D Absorption Stuff >--------------------
  //                     ---------------------
  wsv_data.push_back
    (WsvRecord
     ("t_abs",
      "Temperature associated with the pressures in p_abs [K]",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("z_abs",
      "Vertical altitudes associated with the pressures in p_abs [m]",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("h2o_abs",
      "The total water profile associated with the pressures in p_abs [-]",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("n2_abs",
      "The total nitrogen profile associated with the pressures in p_abs [-]",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("vmrs",
      "The VMRs (unit: absolute number) on the p_abs grid.\n"
      "Dimensions: [tag_groups.nelem(), p_abs.nelem()]",
      Matrix_));

  wsv_data.push_back
    (WsvRecord
     ("abs",
      "The matrix of absorption coefficients (in units of [1/m]).\n"
      "Dimensions: [f_mono.nelem(), p_abs.nelem()]",
      Matrix_));

  wsv_data.push_back
    (WsvRecord
     ("abs_per_tg",
      "These are the absorption coefficients individually for each\n"
      "tag group. The Array contains one matrix for each tag group,\n"
      "the matrix format is the same as that of abs",
      ArrayOfMatrix_));

  wsv_data.push_back
    (WsvRecord
     ("xsec_per_tg",
      "These are the cross sections individually for each tag\n"
      "group. The Array contains one matrix for each tag group,\n"
      "the matrix format is the same as that of abs",
      ArrayOfMatrix_));


  //--------------------< Hydrostatic equilibrium >--------------------
  //                     -------------------------
  wsv_data.push_back
    (WsvRecord
     ("hse",
      "This vector holds the parameters for calculating hydrostatic \n"
      "equilibrium (HSE). The length of the vector is either 1 or 5, where\n"
      "the values are: \n "
      "  1: On/off flag. 0 = ignore HSE, 1 = consider HSE.\n " 
      "  2: The pressure of the reference point [Pa]. \n " 
      "  3: The altitude of the reference point [m]. \n " 
      "  4: Gravitational acceleration at the geoid surface [m/s2]. \n " 
      "  5: Number of iterations of the calculations.\n"
      "If the on/off flag is set to 1, the length of the vector must be 5,\n"
      "while if the flag is 0 a length of 1 is OK.", 
      Vector_));


  //--------------------< RT Stuff >--------------------
  //                     ----------

  wsv_data.push_back
    (WsvRecord
     ("emission",
      "Boolean to include emssion in the calculations.\n"
      "If this variable is set to 0 (zero) pure transmission calculations \n"
      "be simulated and, for example, yCalc will give optical thicknesses \n" 
      "instead of intensities.",
      Index_));

  wsv_data.push_back
    (WsvRecord
     ("za_pencil",
      "Pencil beam zenith angle, the angle between zenith and the LOS [deg].\n"
      "This grid is applied when calculating pencil beam spectra.",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("z_tan",
      "Tangent altitude for the different LOS [m].\n"
      "These tangent altitudes include the effect of refraction (if set). \n"
      "In the case of a ground intersection, a geometrical prolongation \n"
      "below the ground is applied to determine the tangent altitude. \n"
      "For upward observations where there are no tangent altitudes, \n" 
      "z_tan is set to 999 km.",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("z_plat",
      "The vertical altitude, above the geiod, of the platform [m].",
      Numeric_));

  wsv_data.push_back
    (WsvRecord
     ("l_step",
      "The maximum length, along the LOS, between the points of LOS [m].\n"
      "The final step length will in most cases equal the selected length.\n"
      "There are two rare exceptions:\n"
      "  1. Downward observations from within the atmsophere, where the step\n"
      "     length is adjusted downwards to get an integer number of steps\n"
      "     between the sensor and the tangent or ground point.\n"
      "  2. Limb sounding and the distance from the tangent point to the\n"
      "     atmospheric limit (the highest absorption altitude) is smaller\n"
      "     the selected length. The length is then adjusted to this\n"
      "     distance",
      Numeric_));

  wsv_data.push_back
    (WsvRecord
     ("refr",
      "Boolean for inclusion of refraction (0=no refraction, 1=refraction).",
      Index_));

  wsv_data.push_back
    (WsvRecord
     ("refr_lfac",
      "This factor determines the step length used during the ray tracing \n"
      "performed when considering refraction. \n"
      "The step length applied is *l_step* divided by *refr_lfac*. \n" 
      "Accordingly, this factor gives how many ray tracing steps that are \n"
      "performed for each step of the LOS.",
      Index_));

  wsv_data.push_back
    (WsvRecord
     ("refr_model",
      "A string giving what refraction model (or parameterization) to use\n"
      "for the calculation of refractive index.",
      String_));

  wsv_data.push_back
    (WsvRecord
     ("refr_index",
      "The refractive index associated with the pressures in p_refr [-].\n",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("r_geoid",
      "The local curvature radius of the geoid along the LOS [m].",
      Numeric_));

  wsv_data.push_back
    (WsvRecord
     ("z_ground",
      "The vertical altitude above the geiod of the ground [m].",
      Numeric_));

  wsv_data.push_back
    (WsvRecord
     ("t_ground",
      "The physical temperature of the ground [K].",
      Numeric_));

  wsv_data.push_back
    (WsvRecord
     ("e_ground",
      "The ground emission factor for the frequencies in f_mono [0-1].",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("los",
      "Structure to define the line of sight (LOS). See los.h.", 
      Los_));

  wsv_data.push_back
    (WsvRecord
     ("source",
      "Mean source functions between the points of the LOS.",
      ArrayOfMatrix_));

  wsv_data.push_back
    (WsvRecord
     ("trans",
      "The transmissions between the points of the LOS [-].",
      ArrayOfMatrix_));

  wsv_data.push_back
    (WsvRecord
     ("y_space",
      "Radiation entering the atmosphere at the start of the LOS,\n"
      "typically cosmic background radiation.",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("y",
      "The working spectrum.",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("y0",
      "A reference spectrum. This variable can be used e.g. to save a copy\n"
      "of y or to compare the spectra before and after some operation(s).",
      Vector_));


  //--------------------< WF Stuff >--------------------
  //                     ----------
  wsv_data.push_back
    (WsvRecord
     ("absloswfs",
      "Line of sight weighting functions.",
      ArrayOfMatrix_));

  wsv_data.push_back
    (WsvRecord
     ("k_grid",
      "Grid for the retrieval identity for which weighting functions (WFS)\n"
      "shall be calculated (when applicable).\n"
      "For example, pressure altitude grid for species WFs.",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("k",
      "The weighting functions (WFs) for a single retrieval/error identity.",
      Matrix_));

  wsv_data.push_back
    (WsvRecord
     ("k_names",
      "Name(s) on the retrieval identity associated with k.",
      ArrayOfString_));

  wsv_data.push_back
    (WsvRecord
     ("k_aux",
      "Auxiliary data for k. The number of rows of this matrix equals the\n"
      "length of the state vector for the retrieval identity (the number of\n"
      "columns of k).\n"
      "The columns hold different quantities:\n"
      "  Col 1: retrieval grid (or correspondingly)\n"
      "  Col 2: a priori values",
      Matrix_));

  wsv_data.push_back
    (WsvRecord
     ("kx",
      "The state weighting function matrix.",
      Matrix_));

  wsv_data.push_back
    (WsvRecord
     ("kx_names",
      "Names on the retrieval identities associated with kx.",
      ArrayOfString_));

  wsv_data.push_back
    (WsvRecord
     ("kx_lengths",
      "The length of the state vector for each retrieval identity in kx.",
      ArrayOfIndex_));

  wsv_data.push_back
    (WsvRecord
     ("kx_aux",
      "Auxiliary data for kx. As k_aux but with the data of the different\n"
      "retrieval identies appended vertically.",
      Matrix_));

  wsv_data.push_back
    (WsvRecord
     ("kb",
      "The model parameters weighting function matrix.",
      Matrix_));

  wsv_data.push_back
    (WsvRecord
     ("kb_names",
      "Names on the model parameter identities associated with kb.",
      ArrayOfString_));

  wsv_data.push_back
    (WsvRecord
     ("kb_lengths",
      "The length of the model vector for each retrieval identity in kb.",
      ArrayOfIndex_));

  wsv_data.push_back
    (WsvRecord
     ("kb_aux",
      "Auxiliary data for kb. As k_aux but with the data of the different\n"
      "forward model identies appended vertically.",
      Matrix_));


  //-----------------< Sensor and data reduction stuff >------------------
  //                   -------------------------------
  wsv_data.push_back
    (WsvRecord
     ("f_sensor",
      "The centre frequency of the sensor's backend channels [Hz].\n"
      "That is, the frequency vector before any data reduction.\n"
      "It is assumed that the same backend is used for all za_sensor.",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("za_sensor",
      "The centre zenith angle for the spectra recorded by the sensor [deg].\n"
      "That is, the zenith angle vector before any data reduction.",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("f_y",
      "The frequency for every element of y [Hz]. This vector has the same\n"
      "length as y and is mainly for display purposes.\n"
      "If no data reduction is performed f_y = [f_sensor;f_sensor...] where\n"
      "the number of repetitions of f_sensor equals the number of zenith\n"
      "angles. With data reduction there is no general relationship between\n"
      "f_y and f_sensor. If the data reduction is performed using some\n"
      "eigenvectors, f_y can be set to [1;2;3;...;n]",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("za_y",
      "The zenith_angle for every element of y [deg]. This vector has the\n"
      "same length as y and is mainly for display purposes.\n"
      "If no data reduction is performed za_y=[za_sensor(1);za_sensor(1)...]\n"
      "where the number of repetitions of the elements of za_sensor equals\n"
      "the number of frequencies. With data reduction there is no general\n"
      "relationship between za_y and za_sensor. If the data reduction is\n"
      "performed using some eigenvectors, za_y can be set to [1;1;1;...;1]",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("y_cal1",
      "A first calibration spectrum. This spectrum is assumed to be used for\n"
      "all zenith angles. This vector corresponds accordingly to f_sensor.\n"
      "See for example yLoadCalibration for usage of this spectrum.",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("y_cal2",
      "A first calibration spectrum. This spectrum is assumed to be used for\n"
      "all zenith angles. This vector corresponds accordingly to f_sensor.\n"
      "See for example yLoadCalibration for usage of this spectrum.",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("i_cal1",
      "The intensity or brightness temperature corresponding to y_cal1.\n"
      "See for example yLoadCalibration for usage.",
      Vector_));

  wsv_data.push_back
    (WsvRecord
     ("i_cal2",
      "The intensity or brightness temperature corresponding to y_cal2.\n"
      "See for example yLoadCalibration for usage.",
      Vector_));



  //-------------------< Batch calculation stuff >-----------------------
  //                     -----------------------

  wsv_data.push_back
    (WsvRecord
     ("batchname",
      "Default basename for batch data.",
      String_));

  wsv_data.push_back
    (WsvRecord
     ("ybatch",
      "A batch of spectra.\n"
      "The spectra are stored as columns in a matrix",
      Matrix_));

}
