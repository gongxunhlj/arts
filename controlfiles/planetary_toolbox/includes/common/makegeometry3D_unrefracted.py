################################################################################
#                                                                              #
# This is a (plug&play-type) include file. The USER is NOT supposed to MODIFY  #
# it, but choose another include file to suit his/her needs.                   #
#                                                                              #
################################################################################
#                                                                              #
# This INCLUDE file is for                                                     #
#  - NOT considering refraction                                                #
#  - 3D calculations                                                           #
#  - several viewing angles (incl. tangent altitudes) from constant observer   #
#     position                                                                 #
#  - for use with iyCalc (not yCalc)                                           #
#  - for receiver-only setups (no receiver-transmitter paths!)                 #
#                                                                              #
# It performs the following actions:                                           #
#  - sets ppath_agenda: receiver-viewingangle determined path (no transmitter) #
#  - sets ppath_step_agenda: pure geometric ppath calculation (NO refraction)  #
#  - calculates viewing angles from given vector of tangent altitudes          #
#    - considering the (possibly) viewing direction dependent curvature of the #
#      planetary ellipsoid                                                     #
#  - creates a common vector from (given) viewing angle vector and the viewing #
#     angles associated with the tangent altitudes assuming a spherical planet #
#     of equatorial radius of the (possibly) given ellipsoid.                  #
#  - sets sensor positions: constant receiver position, empty transmitter      #
#                                                                              #
# It requires the following input:                                             #
#   viewang_zen     Vector; the zenith viewing angles                          #
#   viewang_azi     Vector; the corresponding azimuth viewing angles           #
#   tanh            Vector; the tangent altitudes                              #
#   tanh_azi        Vector; the tanh corresponding azimuth viewing angles      #
#   obsh            Numeric; the receiver altitude                             #
#   obslat/lon      Numeric; the receiver geographic position                  #
#   refellipsoid    as the WSV                                                 #
#   atmosphere_dim  as the WSV                                                 #
# It also uses (OVERWRITES!) sensor_pos.                                       #
#                                                                              #
# It provides following output:                                                #
#   allzang_zen     Vector; merged zenith viewing angles resulting from        #
#                    viewang_zen and calculated viewing angles resulting from  #
#                    tanh                                                      #
#   allzang_azi     Vector; merged azimuth viewing angles resulting from       #
#                    viewang_azi and tanh_azi                                  #
#                                                                              #
# The file shall NOT be modified by the USER.                                  #
#                                                                              #
# This template creates (and makes internal use of) the following non-WSV:     #
#  (These are created here, i.e., they can not be used by earlier parts of the #
#  script or created again (it also implies, this include can only be included #
#  once in an ARTS run!). They can be used in later parts of the script,       #
#  though.)                                                                    #
#   zang                  Vector                                               #
#   tzang                 Vector                                               #
#   szang                 Numeric                                              #
#   azimuth               Numeric                                              #
#   ntanh                 Index                                                #
#   forloop_agenda_tanh   Agenda                                               #
#                                                                              #
################################################################################

import numpy as np
import pyarts
from pyarts.workspace import Workspace, arts_agenda

ws = Workspace(verbosity=0)
# receiver-viewingangle-path
ws.Copy(ws.ppath_agenda, ws.ppath_agenda__FollowSensorLosPath)
# geometric path calculation (no refraction considered)
ws.Copy(ws.ppath_step_agenda, ws.ppath_step_agenda__GeometricPath)
# DO NOT MODIFY
# preprocessing of viewing geometry parameters
ws.VectorCreate("allang_zen")
ws.VectorCreate("allang_azi")
#
ws.Copy(ws.allang_zen, ws.viewang_zen)
ws.Copy(ws.allang_azi, ws.viewang_azi)
#
ws.ArrayOfIndexCreate("itanh")
ws.Touch(ws.itanh)
ws.NumericCreate("azimuth")
ws.VectorCreate("tzang")
ws.VectorCreate("zang")
ws.Touch(ws.zang)
#
ws.StringSet(ws.tmpformat, "ascii")
# StringSet( tmpformat, "binary" )
ws.StringSet(ws.strtmp, "tmp1.xml")
ws.WriteXML(ws.tmpformat, ws.zang, ws.strtmp, 0)
#
ws.AgendaCreate("forloop_agenda_tanh")


@arts_agenda
def forloop_agenda_tanh(ws):
    ws.ReadXML(out=ws.zang, filename=ws.strtmp)
    ws.Extract(ws.azimuth, ws.tanh_azi, ws.forloop_index)
    ws.Append(ws.itanh, ws.forloop_index)
    ws.Select(ws.tanh, ws.tanh, ws.itanh)
    ws.refellipsoidForAzimuth(ws.refellipsoid, ws.obslat, ws.azimuth)
    ws.VectorZtanToZa1D(ws.tzang, ws.sensor_pos, ws.refellipsoid, 1, ws.tanh)
    ws.Append(ws.zang, ws.tzang)
    ws.WriteXML(ws.tmpformat, ws.zang, ws.strtmp, 0)


ws.forloop_agenda_tanh = forloop_agenda_tanh

#
ws.MatrixSetConstant(ws.sensor_pos, 1, 1, ws.obsh)
ws.IndexCreate("ntanh")
ws.nelemGet(ws.ntanh, ws.tanh)
ws.IndexStepDown(ws.ntanh, ws.ntanh)
ws.Copy(ws.forloop_agenda, ws.forloop_agenda_tanh)
ws.ForLoop(ws.forloop_agenda, 0, ws.ntanh, 1)
#
ws.ReadXML(out=ws.zang, filename=ws.strtmp)
ws.Append(ws.allang_zen, ws.zang)
ws.Append(ws.allang_azi, ws.tanh_azi)
# WriteXML( in=allang_zen )
# Print( allang_zen )
# for use with yCalc (not updated for 3D)
# Matrix1ColFromVector( sensor_los, allang )
# nrowsGet( itmp, sensor_los )
# MatrixSetConstant( sensor_pos, itmp, 1, obsh )
# for use with looped iyCalc, i.e., we have to set rte_pos, not sensor_pos
ws.VectorSetConstant(ws.rte_pos, 1, ws.obsh)
ws.VectorSetConstant(ws.zang, 1, ws.obslat)
# zang just used as container
ws.Append(ws.rte_pos, ws.zang)
ws.VectorSetConstant(ws.zang, 1, ws.obslon)
# zang just used as container
ws.Append(ws.rte_pos, ws.zang)
ws.VectorSet(ws.rte_pos2, [])
