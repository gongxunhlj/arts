# Common part of ARTS setup files for simulations of Odin-SMR measurements.

import numpy as np
import pyarts
from pyarts.workspace import Workspace, arts_agenda

ws = Workspace(verbosity=0)
# ----- Absorption models used for Odin-SMR --------------------------------
ws.abs_cont_descriptionInit()
# ----- H2O continuum ------------------------------------
#
# the conversion factor from dB/km/GHz^2/hPa^2 to arts units
# of 1/m/Hz^2/Pa^2 is 2.30259 * 10^{-26}.
# Note the parameters are deduced using a Van Vleck-Weisskopf
# Present values are taken from Podobedov et al., JQSRT, 2008 (Table 3,
# experiment b).
ws.abs_cont_descriptionAppend(
    ws.abs_cont_names,
    ws.abs_cont_models,
    ws.abs_cont_parameters,
    "H2O-SelfContStandardType",
    "user",
    np.array([9.21e-34, 5.50e00]),
)
ws.abs_cont_descriptionAppend(
    ws.abs_cont_names,
    ws.abs_cont_models,
    ws.abs_cont_parameters,
    "H2O-ForeignContStandardType",
    "user",
    np.array([5.32e-35, 1.80e00]),
)
# ----- O2 continuum models ------------------------------
# Rosenkranz O2 absorption model (only continuum):
ws.abs_cont_descriptionAppend(
    ws.abs_cont_names,
    ws.abs_cont_models,
    ws.abs_cont_parameters,
    "O2-PWR98",
    "RosenkranzContinuum",
    [],
)
# ----- N2 continuum -------------------------------------
#
# the reference for the scaling factor of 1.34 is:
# J. Boissoles et al.
# Theoretical calculation of the translation-rotation collision-induced
# absorption in N2-N2, O2-O2, and N2-O2 pairs
# JQSRT, vol. 82 (2003) 505-516.
# For the Odin frequencies it is sufficient to use this constant
# scaling factor and not the frequency dependent factors given in the paper.
# The scaling incluses CIA contributions from O2-O2 and N2-O2 besides
# the original N2-N2 CIA.
# One has to note that Boissoles et al. used their own N2-N2- CIa model
# and not the B&F model to deduce this scaling factors. However, for the
# Odin frequencies the difference between these two models should be
# very small, implying that the 1.34 scaling factor is also appropriate
# in connection with the B&F model within the uncertainty range.
# MPM93 N2 continuum model:
ws.abs_cont_descriptionAppend(
    ws.abs_cont_names,
    ws.abs_cont_models,
    ws.abs_cont_parameters,
    "N2-SelfContMPM93",
    "MPM93Scale",
    np.array([1.34]),
)
# ----- End of absorption models used for Odin-SMR ------------------------
# Odin-SMR gives RJ brightness temperatures
ws.StringSet(ws.iy_unit, "RJBT")
# A RT step length of 20 km is applied in operational processing
ws.NumericSet(ws.ppath_lmax, 20000.0)
