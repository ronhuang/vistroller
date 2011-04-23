/*==============================================================================
            Copyright (c) 2010 QUALCOMM Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary

@file
    C_object.h

@brief
    Geometry for the C object used in the samples.

==============================================================================*/
#ifndef _C_OBJECT_H_
#define _C_OBJECT_H_


#define NUM_C_OBJECT_VERTEX 372
#define NUM_C_OBJECT_INDEX 428 * 3


static const float CobjectVertices[NUM_C_OBJECT_VERTEX * 3] =
{
    1.546282, 0.836379, 0.116930,  1.425000, 0.798440, 0.016930,  1.379048, 0.853364, 0.116930,  1.558334, 0.784898, 0.016930,  1.582369, 2.035883, 0.116931,  1.677431, 1.844795, 0.016931,  1.549219, 1.998440, 0.016931,  1.719338, 1.867535, 0.116931,  0.562591, 1.329230, 0.116931,  0.500000, 1.100001, 0.016930,  0.513802, 1.338977, 0.016930,  0.550000, 1.100001, 0.116930,  0.985939, 0.350000, 0.116930,  1.096963, 0.316320, 0.016930,  0.985939, 0.300000, 0.016930,  1.082663, 0.364649, 0.116930,  1.249246, 0.481845, 0.116930,  1.355903, 0.551217, 0.016930,  1.285157, 0.446877, 0.016930,  1.313227, 0.581722, 0.116930,  1.355903, 0.551216, 1.000000,  1.249246, 0.481844, 0.900000,  1.285157, 0.446876, 1.000000,  1.313227, 0.581721, 0.900000,  1.425000, 0.798440, 1.000000,  1.356494, 0.705562, 0.900000,  1.402518, 0.668405, 1.000000,  1.379048, 0.853364, 0.900000,  1.356494, 0.705562, 0.116930,  1.425000, 0.798440, 0.016930,  1.402518, 0.668405, 0.016930,  1.379048, 0.853364, 0.116930,  1.096963, 0.316320, 1.000000,  0.985939, 0.350000, 0.900000,  0.985939, 0.300000, 1.000000,  1.082663, 0.364649, 0.900000,  1.285157, 0.446876, 1.000000,  1.170432, 0.408597, 0.900000,  1.196702, 0.365278, 1.000000,  1.249246, 0.481844, 0.900000,  1.170432, 0.408597, 0.116930,  1.285157, 0.446877, 0.016930,  1.196702, 0.365278, 0.016930,  1.249246, 0.481845, 0.116930,  0.761165, 0.432158, 0.116930,  0.633594, 0.502345, 0.016930,  0.672046, 0.534853, 0.116930,  0.732119, 0.389931, 0.016930,  0.761165, 0.432157, 0.900000,  0.633594, 0.502344, 1.000000,  0.732119, 0.389931, 1.000000,  0.672046, 0.534853, 0.900000,  0.849567, 0.322483, 1.000000,  0.865796, 0.370539, 0.900000,  0.732119, 0.389931, 1.000000,  0.761165, 0.432157, 0.900000,  0.849567, 0.322483, 0.016930,  0.865796, 0.370539, 0.116930,  0.761165, 0.432158, 0.116930,  0.732119, 0.389931, 0.016930,  0.604243, 0.679804, 0.116930,  0.514844, 0.857900, 0.016930,  0.563561, 0.868187, 0.116930,  0.559375, 0.658682, 0.016930,  0.604243, 0.679804, 0.900000,  0.514844, 0.857900, 1.000000,  0.559375, 0.658682, 1.000000,  0.563561, 0.868187, 0.900000,  0.500000, 1.100001, 1.000000,  0.562591, 1.329230, 0.900000,  0.513802, 1.338977, 1.000000,  0.550000, 1.100001, 0.900000,  1.155779, 1.792074, 0.116931,  1.328993, 1.670141, 0.016930,  1.292905, 1.618291, 0.116931,  1.178473, 1.842537, 0.016931,  0.748140, 1.766696, 0.116931,  0.624219, 1.694534, 0.016930,  0.718230, 1.808683, 0.016931,  0.663319, 1.662564, 0.116931,  0.624219, 1.694533, 1.000000,  0.748140, 1.766695, 0.900000,  0.718230, 1.808683, 1.000000,  0.663319, 1.662563, 0.900000,  0.600364, 1.516751, 0.900000,  0.555209, 1.537155, 1.000000,  0.600364, 1.516751, 0.116931,  0.555209, 1.537155, 0.016930,  0.851514, 1.829176, 0.116931,  0.973439, 1.900002, 0.016931,  0.973439, 1.850002, 0.116931,  0.834636, 1.877172, 0.016931,  0.851514, 1.829176, 0.900000,  0.973439, 1.900002, 1.000000,  0.834636, 1.877172, 1.000000,  0.973439, 1.850002, 0.900000,  0.718230, 1.808683, 1.000000,  0.748140, 1.766695, 0.900000,  0.748140, 1.766696, 0.116931,  0.718230, 1.808683, 0.016931,  1.155779, 1.792074, 0.900000,  1.328993, 1.670140, 1.000000,  1.178473, 1.842537, 1.000000,  1.292905, 1.618291, 0.900000,  1.178473, 1.842537, 1.000000,  1.155779, 1.792074, 0.900000,  1.155779, 1.792074, 0.116931,  1.178473, 1.842537, 0.016931,  1.548995, 1.344685, 0.116931,  1.691667, 1.408856, 0.016930,  1.714809, 1.360878, 0.116931,  1.558334, 1.395835, 0.016930,  1.548995, 1.344685, 0.900000,  1.691667, 1.408856, 1.000000,  1.558334, 1.395835, 1.000000,  1.714809, 1.360878, 0.900000,  1.425000, 1.382815, 1.000000,  1.384816, 1.328653, 0.900000,  1.425000, 1.382815, 1.000000,  1.384816, 1.328653, 0.900000,  1.425000, 1.382815, 0.016930,  1.384816, 1.328653, 0.116931,  1.384816, 1.328653, 0.116931,  1.425000, 1.382815, 0.016930,  1.819301, 1.647984, 0.116931,  1.825000, 1.421876, 0.016930,  1.769358, 1.652607, 0.016930,  1.882257, 1.377230, 0.116931,  1.825000, 1.421876, 1.000000,  1.819301, 1.647983, 0.900000,  1.769358, 1.652606, 1.000000,  1.882257, 1.377230, 0.900000,  1.825000, 1.421876, 1.000000,  1.882257, 1.377230, 0.900000,  1.882257, 1.377230, 0.116931,  1.825000, 1.421876, 0.016930,  1.677431, 1.844795, 1.000000,  1.582369, 2.035883, 0.900000,  1.549219, 1.998440, 1.000000,  1.719338, 1.867535, 0.900000,  0.156713, 0.524794, 0.116930,  0.280208, 0.389237, 0.016930,  0.238345, 0.361709, 0.116930,  0.202344, 0.545315, 0.016930,  0.302688, 1.928176, 0.116931,  0.519792, 2.064238, 0.016931,  0.339844, 1.894534, 0.016931,  0.492473, 2.106968, 0.116931,  1.000000, 2.250002, 0.116931,  1.207552, 2.177606, 0.016931,  1.000000, 2.200002, 0.016931,  1.219890, 2.226211, 0.116931,  1.207552, 2.177606, 1.000000,  1.000000, 2.250002, 0.900000,  1.000000, 2.200002, 1.000000,  1.219890, 2.226211, 0.900000,  1.582369, 2.035883, 0.900000,  1.390625, 2.110419, 1.000000,  1.549219, 1.998440, 1.000000,  1.414013, 2.154838, 0.900000,  1.390625, 2.110419, 0.016931,  1.582369, 2.035883, 0.116931,  1.549219, 1.998440, 0.016931,  1.414013, 2.154838, 0.116931,  0.519792, 2.064238, 1.000000,  0.302688, 1.928176, 0.900000,  0.339844, 1.894534, 1.000000,  0.492473, 2.106968, 0.900000,  0.739844, 2.166061, 1.000000,  0.724910, 2.214244, 0.900000,  0.739844, 2.166061, 0.016931,  0.724910, 2.214244, 0.116931,  0.050000, 1.101564, 0.116930,  0.126649, 1.406338, 0.016930,  0.100000, 1.101564, 0.016930,  0.078076, 1.417758, 0.116931,  0.126649, 1.406338, 1.000000,  0.050000, 1.101564, 0.900000,  0.100000, 1.101564, 1.000000,  0.078076, 1.417758, 0.900000,  0.339844, 1.894534, 1.000000,  0.162306, 1.693295, 0.900000,  0.206597, 1.670662, 1.000000,  0.302688, 1.928176, 0.900000,  0.162306, 1.693296, 0.116931,  0.339844, 1.894534, 0.016931,  0.206597, 1.670663, 0.016930,  0.302688, 1.928176, 0.116931,  0.061857, 0.897715, 0.116930,  0.145486, 0.718926, 0.016930,  0.097428, 0.705458, 0.116930,  0.111372, 0.904342, 0.016930,  0.061857, 0.897715, 0.900000,  0.145486, 0.718926, 1.000000,  0.111372, 0.904342, 1.000000,  0.097428, 0.705458, 0.900000,  0.156713, 0.524794, 0.900000,  0.280208, 0.389237, 1.000000,  0.202344, 0.545314, 1.000000,  0.238345, 0.361709, 0.900000,  1.223771, -0.024825, 0.116930,  1.405036, 0.094792, 0.016930,  1.429105, 0.050702, 0.116930,  1.211025, 0.023698, 0.016930,  0.464550, 0.106246, 0.116930,  0.632466, 0.065278, 0.016930,  0.611871, 0.019442, 0.116930,  0.493751, 0.146876, 0.016930,  0.464550, 0.106246, 0.900000,  0.632466, 0.065278, 1.000000,  0.493751, 0.146876, 1.000000,  0.611871, 0.019442, 0.900000,  0.377344, 0.256425, 1.000000,  0.340957, 0.222193, 0.900000,  0.340957, 0.222193, 0.900000,  0.377344, 0.256425, 1.000000,  0.377344, 0.256425, 0.016930,  0.340957, 0.222193, 0.116930,  0.340957, 0.222193, 0.116930,  0.377344, 0.256425, 0.016930,  0.985939, -0.050000, 0.116930,  0.796529, 0.016320, 0.016930,  0.985939, 0.000000, 0.016930,  0.785667, -0.032639, 0.116930,  0.796529, 0.016320, 1.000000,  0.985939, -0.050000, 0.900000,  0.985939, 0.000000, 1.000000,  0.785667, -0.032639, 0.900000,  1.223771, -0.024825, 0.900000,  1.405036, 0.094792, 1.000000,  1.211025, 0.023698, 1.000000,  1.429105, 0.050702, 0.900000,  1.737241, 0.346824, 0.116930,  1.780470, 0.550088, 0.016930,  1.829974, 0.555455, 0.116930,  1.694793, 0.368577, 0.016930,  1.737241, 0.346824, 0.900000,  1.780470, 0.550087, 1.000000,  1.694793, 0.368577, 1.000000,  1.829974, 0.555454, 0.900000,  1.601940, 0.176578, 0.900000,  1.567970, 0.213281, 1.000000,  1.601940, 0.176578, 0.900000,  1.567970, 0.213281, 1.000000,  1.601940, 0.176578, 0.116930,  1.567970, 0.213281, 0.016930,  1.601940, 0.176578, 0.116930,  1.567970, 0.213281, 0.016930,  1.713313, 0.819415, 0.116930,  1.825000, 0.757814, 0.016930,  1.691667, 0.771356, 0.016930,  1.880139, 0.802472, 0.116930,  1.825000, 0.757814, 1.000000,  1.713313, 0.819415, 0.900000,  1.691667, 0.771356, 1.000000,  1.880139, 0.802472, 0.900000,  1.825000, 0.757814, 1.000000,  1.880139, 0.802472, 0.900000,  1.880139, 0.802472, 0.116930,  1.825000, 0.757814, 0.016930,  1.546282, 0.836379, 0.900000,  1.425000, 0.798440, 1.000000,  1.558334, 0.784898, 1.000000,  1.379048, 0.853364, 0.900000,  1.769358, 1.652606, 1.000000,  1.691667, 1.408856, 1.000000,  1.825000, 1.421876, 1.000000,  1.691667, 0.771356, 1.000000,  1.780470, 0.550087, 1.000000,  1.825000, 0.757814, 1.000000,  1.402518, 0.668405, 1.000000,  1.558334, 0.784898, 1.000000,  1.425000, 0.798440, 1.000000,  1.558334, 1.395835, 1.000000,  1.328993, 1.670140, 1.000000,  1.425000, 1.382815, 1.000000,  1.677431, 1.844795, 1.000000,  1.549219, 1.998440, 1.000000,  1.178473, 1.842537, 1.000000,  1.390625, 2.110419, 1.000000,  1.207552, 2.177606, 1.000000,  0.973439, 1.900002, 1.000000,  1.000000, 2.200002, 1.000000,  0.739844, 2.166061, 1.000000,  0.834636, 1.877172, 1.000000,  0.519792, 2.064238, 1.000000,  0.718230, 1.808683, 1.000000,  0.339844, 1.894534, 1.000000,  0.624219, 1.694533, 1.000000,  0.206597, 1.670662, 1.000000,  0.555209, 1.537155, 1.000000,  0.126649, 1.406338, 1.000000,  0.513802, 1.338977, 1.000000,  0.100000, 1.101564, 1.000000,  0.500000, 1.100001, 1.000000,  0.111372, 0.904342, 1.000000,  0.514844, 0.857900, 1.000000,  0.145486, 0.718926, 1.000000,  0.559375, 0.658682, 1.000000,  0.202344, 0.545314, 1.000000,  0.280208, 0.389237, 1.000000,  0.633594, 0.502344, 1.000000,  0.377344, 0.256425, 1.000000,  0.493751, 0.146876, 1.000000,  0.732119, 0.389931, 1.000000,  0.632466, 0.065278, 1.000000,  0.849567, 0.322483, 1.000000,  0.796529, 0.016320, 1.000000,  0.985939, 0.000000, 1.000000,  0.985939, 0.300000, 1.000000,  1.211025, 0.023698, 1.000000,  1.096963, 0.316320, 1.000000,  1.405036, 0.094792, 1.000000,  1.196702, 0.365278, 1.000000,  1.567970, 0.213281, 1.000000,  1.285157, 0.446876, 1.000000,  1.694793, 0.368577, 1.000000,  1.355903, 0.551216, 1.000000,  1.691667, 1.408856, 0.016930,  1.769358, 1.652607, 0.016930,  1.825000, 1.421876, 0.016930,  1.780470, 0.550088, 0.016930,  1.691667, 0.771356, 0.016930,  1.825000, 0.757814, 0.016930,  1.558334, 0.784898, 0.016930,  1.402518, 0.668405, 0.016930,  1.425000, 0.798440, 0.016930,  1.328993, 1.670141, 0.016930,  1.558334, 1.395835, 0.016930,  1.425000, 1.382815, 0.016930,  1.677431, 1.844795, 0.016931,  1.549219, 1.998440, 0.016931,  1.178473, 1.842537, 0.016931,  1.390625, 2.110419, 0.016931,  1.207552, 2.177606, 0.016931,  0.973439, 1.900002, 0.016931,  1.000000, 2.200002, 0.016931,  0.739844, 2.166061, 0.016931,  0.834636, 1.877172, 0.016931,  0.519792, 2.064238, 0.016931,  0.718230, 1.808683, 0.016931,  0.339844, 1.894534, 0.016931,  0.624219, 1.694534, 0.016930,  0.206597, 1.670663, 0.016930,  0.555209, 1.537155, 0.016930,  0.126649, 1.406338, 0.016930,  0.513802, 1.338977, 0.016930,  0.100000, 1.101564, 0.016930,  0.500000, 1.100001, 0.016930,  0.111372, 0.904342, 0.016930,  0.514844, 0.857900, 0.016930,  0.145486, 0.718926, 0.016930,  0.559375, 0.658682, 0.016930,  0.202344, 0.545315, 0.016930,  0.280208, 0.389237, 0.016930,  0.633594, 0.502345, 0.016930,  0.377344, 0.256425, 0.016930,  0.732119, 0.389931, 0.016930,  0.493751, 0.146876, 0.016930,  0.632466, 0.065278, 0.016930,  0.849567, 0.322483, 0.016930,  0.796529, 0.016320, 0.016930,  0.985939, 0.000000, 0.016930,  0.985939, 0.300000, 0.016930,  1.211025, 0.023698, 0.016930,  1.096963, 0.316320, 0.016930,  1.405036, 0.094792, 0.016930,  1.196702, 0.365278, 0.016930,  1.567970, 0.213281, 0.016930,  1.285157, 0.446877, 0.016930,  1.694793, 0.368577, 0.016930,  1.355903, 0.551217, 0.016930
};

static const float CobjectTexCoords[NUM_C_OBJECT_VERTEX * 2] =
{
    0.238897, 0.706427,  0.191843, 0.751881,  0.209221, 0.769131,  0.191843, 0.701826,  0.210177, 0.020540,  0.192896, 0.092275,  0.192896, 0.034596,  0.239688, 0.102960,  0.860943, 0.920842,  0.821765, 0.995000,  0.877987, 0.995000,  0.821707, 0.920842,  0.061628, 0.164281,  0.005000, 0.109921,  0.005000, 0.158712,  0.061628, 0.115185,  0.011077, 0.953327,  0.023132, 0.995000,  0.005000, 0.995000,  0.032597, 0.882163,  0.023132, 0.585326,  0.011077, 0.626999,  0.005000, 0.585326,  0.032597, 0.769326,  0.066094, 0.585326,  0.054118, 0.698163,  0.043497, 0.585326,  0.075639, 0.626999,  0.054118, 0.810999,  0.066094, 0.995000,  0.043497, 0.995000,  0.075639, 0.953327,  0.174885, 0.109921,  0.118257, 0.164281,  0.174885, 0.158712,  0.118257, 0.115185,  0.174885, 0.027216,  0.128093, 0.071201,  0.174885, 0.066089,  0.157604, 0.042998,  0.081302, 0.071201,  0.005000, 0.027216,  0.005000, 0.066089,  0.022281, 0.042998,  0.664646, 0.972369,  0.681159, 0.995000,  0.703911, 0.895078,  0.654712, 0.995000,  0.664646, 0.795155,  0.681159, 0.772524,  0.654712, 0.772524,  0.703911, 0.833801,  0.174885, 0.218642,  0.128093, 0.217269,  0.174885, 0.270256,  0.157604, 0.257492,  0.005000, 0.218642,  0.081302, 0.217269,  0.022281, 0.257492,  0.005000, 0.270256,  0.743186, 0.920842,  0.764808, 0.995000,  0.782470, 0.920842,  0.717939, 0.995000,  0.743186, 0.846683,  0.764807, 0.772524,  0.717939, 0.772524,  0.782470, 0.846683,  0.821765, 0.772524,  0.860943, 0.846683,  0.877987, 0.772524,  0.821707, 0.846683,  0.022281, 0.338236,  0.005000, 0.391821,  0.081302, 0.440064,  0.005000, 0.316059,  0.978613, 0.972369,  0.961636, 0.995000,  0.988491, 0.995000,  0.939398, 0.933723,  0.961636, 0.772524,  0.978613, 0.795155,  0.988491, 0.772524,  0.939398, 0.872447,  0.900175, 0.846683,  0.924611, 0.772524,  0.900175, 0.920842,  0.924611, 0.995000,  0.120411, 0.882163,  0.138101, 0.995000,  0.147071, 0.810999,  0.113980, 0.995000,  0.120411, 0.769326,  0.138101, 0.585326,  0.113980, 0.585326,  0.147071, 0.698163,  0.093751, 0.585326,  0.098949, 0.626999,  0.098949, 0.953327,  0.093751, 0.995000,  0.157604, 0.338236,  0.174885, 0.391821,  0.174885, 0.316059,  0.098583, 0.440064,  0.173731, 0.585326,  0.169788, 0.626999,  0.169788, 0.953327,  0.173731, 0.995000,  0.238897, 0.932753,  0.191843, 0.879806,  0.268573, 0.870505,  0.191843, 0.929860,  0.285951, 0.932753,  0.362680, 0.879806,  0.362680, 0.929860,  0.315626, 0.870505,  0.174885, 0.518090,  0.157604, 0.541892,  0.362680, 0.979915,  0.345302, 0.995000,  0.005000, 0.518090,  0.022281, 0.541892,  0.209221, 0.995000,  0.191843, 0.979915,  0.269198, 0.185381,  0.192896, 0.251041,  0.192896, 0.164424,  0.210177, 0.267802,  0.362781, 0.251041,  0.315990, 0.185381,  0.362781, 0.164424,  0.345500, 0.267802,  0.362680, 0.829752,  0.345302, 0.808258,  0.209221, 0.808258,  0.191843, 0.829752,  0.362781, 0.092275,  0.345500, 0.020540,  0.362781, 0.034596,  0.286479, 0.102960,  0.722733, 0.674779,  0.687776, 0.748938,  0.688722, 0.674779,  0.718668, 0.748938,  0.380792, 0.726307,  0.423764, 0.748938,  0.388146, 0.748938,  0.424739, 0.687661,  0.513607, 0.674779,  0.559894, 0.748938,  0.518813, 0.748938,  0.554869, 0.674779,  0.559894, 0.526462,  0.513607, 0.600621,  0.518813, 0.526462,  0.554869, 0.600621,  0.634083, 0.549093,  0.596130, 0.526462,  0.627521, 0.526462,  0.594476, 0.587739,  0.596130, 0.748938,  0.634083, 0.726307,  0.627521, 0.748938,  0.594476, 0.649015,  0.423764, 0.526462,  0.380792, 0.549093,  0.388146, 0.526462,  0.424739, 0.626385,  0.467320, 0.526462,  0.468685, 0.600621,  0.467320, 0.748938,  0.468685, 0.674779,  0.840393, 0.674779,  0.889093, 0.748938,  0.828768, 0.748938,  0.891056, 0.674779,  0.889093, 0.526462,  0.840393, 0.600621,  0.828768, 0.526462,  0.891056, 0.600621,  0.985723, 0.526462,  0.941718, 0.587739,  0.941411, 0.526462,  0.992382, 0.549093,  0.941718, 0.649015,  0.985723, 0.748938,  0.941411, 0.748938,  0.992382, 0.726307,  0.796713, 0.674779,  0.753032, 0.748938,  0.757690, 0.674779,  0.789732, 0.748938,  0.796713, 0.600621,  0.753032, 0.526462,  0.789732, 0.526462,  0.757690, 0.600621,  0.722733, 0.600621,  0.687776, 0.526462,  0.718668, 0.526462,  0.688722, 0.626385,  0.554038, 0.920842,  0.594293, 0.995000,  0.593919, 0.920842,  0.555366, 0.995000,  0.412705, 0.933723,  0.439281, 0.995000,  0.444619, 0.920842,  0.411449, 0.995000,  0.412705, 0.872447,  0.439281, 0.772524,  0.411449, 0.772524,  0.444619, 0.846683,  0.661488, 0.526462,  0.654712, 0.549093,  0.380792, 0.795155,  0.388093, 0.772524,  0.661488, 0.748938,  0.654712, 0.726307,  0.380792, 0.972369,  0.388093, 0.995000,  0.513783, 0.920842,  0.472200, 0.995000,  0.510204, 0.995000,  0.476532, 0.920842,  0.472200, 0.772524,  0.513783, 0.846683,  0.510204, 0.772524,  0.476532, 0.846683,  0.554038, 0.846683,  0.594293, 0.772524,  0.555366, 0.772524,  0.593919, 0.872447,  0.239688, 0.463571,  0.192896, 0.401675,  0.269198, 0.385250,  0.192896, 0.469815,  0.286479, 0.463571,  0.362781, 0.401675,  0.362781, 0.469815,  0.315990, 0.385250,  0.633800, 0.795155,  0.626984, 0.772524,  0.345500, 0.541892,  0.362781, 0.528114,  0.633800, 0.972369,  0.626984, 0.995000,  0.210177, 0.541892,  0.192896, 0.528114,  0.268573, 0.643723,  0.191843, 0.601718,  0.191843, 0.651772,  0.209221, 0.581019,  0.362680, 0.601718,  0.315626, 0.643723,  0.362680, 0.651772,  0.345302, 0.581019,  0.362781, 0.323693,  0.345500, 0.306928,  0.210177, 0.306928,  0.192896, 0.323693,  0.285951, 0.706427,  0.362680, 0.751881,  0.362680, 0.701826,  0.345302, 0.769131,  0.985385, 0.128879,  0.971959, 0.184042,  0.995000, 0.181095,  0.971959, 0.328313,  0.987305, 0.378387,  0.995000, 0.331377,  0.921991, 0.351611,  0.948917, 0.325248,  0.925876, 0.322183,  0.948917, 0.186988,  0.909285, 0.124911,  0.925876, 0.189935,  0.969499, 0.085386,  0.947342, 0.050615,  0.883273, 0.085897,  0.919935, 0.025273,  0.888298, 0.010068,  0.847841, 0.072892,  0.852431, 0.005000,  0.807473, 0.012681,  0.823855, 0.078059,  0.769446, 0.035724,  0.803738, 0.093558,  0.738349, 0.074130,  0.787492, 0.119391,  0.715323, 0.124793,  0.775567, 0.155007,  0.701507, 0.184612,  0.768411, 0.199856,  0.696902, 0.253584,  0.766026, 0.253938,  0.698867, 0.298217,  0.768591, 0.308727,  0.704762, 0.340178,  0.776286, 0.353811,  0.714588, 0.379467,  0.728043, 0.414789,  0.789112, 0.389192,  0.744830, 0.444845,  0.764946, 0.469637,  0.806138, 0.414631,  0.788917, 0.488103,  0.826435, 0.429895,  0.817269, 0.499182,  0.850001, 0.502876,  0.850001, 0.434983,  0.888899, 0.497513,  0.869187, 0.431290,  0.922426, 0.481423,  0.886423, 0.420211,  0.950582, 0.454609,  0.901709, 0.401744,  0.972499, 0.419464,  0.913935, 0.378132,  0.655849, 0.184042,  0.669275, 0.128879,  0.678890, 0.181095,  0.671195, 0.378387,  0.655849, 0.328313,  0.678890, 0.331377,  0.632808, 0.325248,  0.605881, 0.351611,  0.609766, 0.322183,  0.593175, 0.124911,  0.632808, 0.186988,  0.609766, 0.189935,  0.653389, 0.085386,  0.631233, 0.050615,  0.567164, 0.085897,  0.603826, 0.025273,  0.572189, 0.010068,  0.531732, 0.072892,  0.536322, 0.005000,  0.491364, 0.012681,  0.507745, 0.078059,  0.453337, 0.035724,  0.487629, 0.093558,  0.422240, 0.074130,  0.471383, 0.119391,  0.399213, 0.124793,  0.459457, 0.155007,  0.385397, 0.184611,  0.452302, 0.199856,  0.380792, 0.253584,  0.449916, 0.253938,  0.382757, 0.298217,  0.452482, 0.308727,  0.388653, 0.340178,  0.460177, 0.353811,  0.398478, 0.379467,  0.411934, 0.414789,  0.473003, 0.389192,  0.428720, 0.444845,  0.490029, 0.414631,  0.448836, 0.469637,  0.472808, 0.488103,  0.510325, 0.429895,  0.501160, 0.499182,  0.533892, 0.502876,  0.533892, 0.434983,  0.572789, 0.497513,  0.553078, 0.431290,  0.606316, 0.481423,  0.570314, 0.420211,  0.634473, 0.454609,  0.585600, 0.401744,  0.656389, 0.419464,  0.597826, 0.378132
};

static const float CobjectNormals[NUM_C_OBJECT_VERTEX * 3] =
{
    0.097137, 0.956410, -0.275397,  -0.493883, 0.651127, -0.576293,  -0.429519, 0.867101, -0.252289,  0.090377, 0.889850, -0.447213,  0.672757, 0.692735, -0.259839,  0.739025, 0.514567, -0.434813,  0.606506, 0.657393, -0.447197,  0.831652, 0.491616, -0.258202,  0.968272, -0.100319, -0.228878,  0.895589, 0.001592, -0.444879,  0.886471, -0.137802, -0.441791,  0.973239, 0.001732, -0.229790,  -0.014653, 0.964375, -0.264133,  -0.221516, 0.865741, -0.448801,  0.007840, 0.894400, -0.447200,  -0.316604, 0.906733, -0.278562,  -0.769428, 0.594508, -0.233540,  -0.774957, 0.438459, -0.455187,  -0.655795, 0.608353, -0.447034,  -0.866120, 0.406607, -0.290701,  -0.774957, 0.438459, 0.455187,  -0.742105, 0.628225, 0.233694,  -0.655796, 0.608353, 0.447033,  -0.883681, 0.419401, 0.207872,  -0.493883, 0.651127, 0.576293,  -0.930910, 0.217672, 0.293301,  -0.845464, 0.257123, 0.468058,  -0.728889, 0.636356, 0.252531,  -0.951135, 0.226655, -0.209690,  -0.493883, 0.651127, -0.576293,  -0.845464, 0.257123, -0.468058,  -0.429519, 0.867101, -0.252289,  -0.221516, 0.865741, 0.448801,  0.032561, 0.963936, 0.264135,  0.007840, 0.894400, 0.447200,  -0.315099, 0.927913, 0.199222,  -0.655796, 0.608353, 0.447033,  -0.568401, 0.774290, 0.278200,  -0.470585, 0.758946, 0.450057,  -0.742105, 0.628225, 0.233694,  -0.573598, 0.794613, -0.198936,  -0.655795, 0.608353, -0.447034,  -0.470585, 0.758946, -0.450057,  -0.769428, 0.594508, -0.233540,  0.636207, 0.718762, -0.280396,  0.724976, 0.523950, -0.447086,  0.831635, 0.519190, -0.197038,  0.528666, 0.718006, -0.452747,  0.642628, 0.739467, 0.200543,  0.724976, 0.523951, 0.447085,  0.528666, 0.718006, 0.452747,  0.819316, 0.502782, 0.275557,  0.250262, 0.857080, 0.450314,  0.359196, 0.889973, 0.280939,  0.528666, 0.718006, 0.452747,  0.642628, 0.739467, 0.200543,  0.250262, 0.857080, -0.450314,  0.357690, 0.911958, -0.200975,  0.636207, 0.718762, -0.280396,  0.528666, 0.718006, -0.452747,  0.917538, 0.288718, -0.273433,  0.884869, 0.147059, -0.442019,  0.972841, 0.122810, -0.196208,  0.837724, 0.321925, -0.441115,  0.933688, 0.300022, 0.195483,  0.884869, 0.147059, 0.442019,  0.837724, 0.321925, 0.441115,  0.954520, 0.116368, 0.274498,  0.895589, 0.001592, 0.444879,  0.965405, -0.124821, 0.228938,  0.886471, -0.137802, 0.441791,  0.988267, 0.001759, 0.152729,  -0.577774, -0.754976, -0.310142,  -0.739675, -0.472800, -0.478896,  -0.852271, -0.457737, -0.253200,  -0.405145, -0.785401, -0.467977,  0.659060, -0.724606, -0.201460,  0.740478, -0.501329, -0.447618,  0.540591, -0.707884, -0.454601,  0.834232, -0.477564, -0.275661,  0.740478, -0.501329, 0.447618,  0.652445, -0.703555, 0.281649,  0.540590, -0.707884, 0.454601,  0.847072, -0.493574, 0.197112,  0.923334, -0.269985, 0.273060,  0.845635, -0.301271, 0.440609,  0.939792, -0.280508, -0.195207,  0.845635, -0.301271, -0.440609,  0.328809, -0.891657, -0.311178,  0.017967, -0.893356, -0.448990,  -0.094387, -0.974284, -0.204601,  0.303512, -0.838016, -0.453443,  0.337110, -0.911848, 0.234288,  0.017967, -0.893356, 0.448990,  0.303512, -0.838016, 0.453443,  -0.103540, -0.952688, 0.285771,  0.540590, -0.707884, 0.454601,  0.652445, -0.703555, 0.281649,  0.659060, -0.724606, -0.201460,  0.540591, -0.707884, -0.454601,  -0.581271, -0.782738, 0.222363,  -0.739675, -0.472800, 0.478896,  -0.405145, -0.785402, 0.467976,  -0.880198, -0.401686, 0.252783,  -0.405145, -0.785402, 0.467976,  -0.581271, -0.782738, 0.222363,  -0.577774, -0.754976, -0.310142,  -0.405145, -0.785401, -0.467977,  0.092548, -0.947718, -0.305394,  0.086931, -0.890192, -0.447214,  0.095290, -0.975798, -0.196819,  0.086931, -0.890192, -0.447214,  0.094592, -0.968641, 0.229753,  0.086931, -0.890193, 0.447214,  0.086931, -0.890192, 0.447214,  0.093433, -0.956779, 0.275397,  -0.454167, -0.701037, 0.549799,  -0.522071, -0.797844, 0.301474,  -0.454167, -0.701037, 0.549799,  -0.522071, -0.797844, 0.301474,  -0.454167, -0.701037, -0.549799,  -0.537257, -0.818786, -0.202349,  -0.537257, -0.818786, -0.202349,  -0.454167, -0.701037, -0.549799,  0.934620, 0.305248, -0.182510,  0.659531, -0.463678, -0.591626,  0.845595, 0.328347, -0.420901,  0.770771, -0.547849, -0.325228,  0.659531, -0.463678, 0.591626,  0.920610, 0.295435, 0.255333,  0.845594, 0.328348, 0.420901,  0.794240, -0.566416, 0.219898,  0.659531, -0.463678, 0.591626,  0.794240, -0.566416, 0.219898,  0.770771, -0.547849, -0.325228,  0.659531, -0.463678, -0.591626,  0.739025, 0.514567, 0.434813,  0.643364, 0.720121, 0.259824,  0.606506, 0.657393, 0.447197,  0.842872, 0.505459, 0.184601,  -0.883823, -0.378253, -0.275285,  -0.776215, -0.443768, -0.447839,  -0.831181, -0.506316, -0.229742,  -0.835424, -0.319598, -0.447129,  -0.729589, 0.643963, -0.230241,  -0.499572, 0.739006, -0.451994,  -0.722858, 0.526700, -0.447284,  -0.544348, 0.805915, -0.232779,  0.006983, 0.964880, -0.262598,  0.167794, 0.878264, -0.447770,  -0.009975, 0.894383, -0.447191,  0.240943, 0.930430, -0.276127,  0.167794, 0.878264, 0.447769,  -0.027920, 0.964502, 0.262596,  -0.009975, 0.894383, 0.447190,  0.239126, 0.950707, 0.197420,  0.643364, 0.720121, 0.259824,  0.415459, 0.791220, 0.448737,  0.606506, 0.657393, 0.447197,  0.452530, 0.861383, 0.230727,  0.415459, 0.791220, -0.448737,  0.672757, 0.692735, -0.259839,  0.606506, 0.657393, -0.447197,  0.459576, 0.874793, -0.153388,  -0.499572, 0.739006, 0.451994,  -0.760151, 0.607497, 0.230473,  -0.722857, 0.526701, 0.447284,  -0.552961, 0.818707, 0.154768,  -0.203986, 0.869841, 0.449183,  -0.293126, 0.914715, 0.278162,  -0.203986, 0.869841, -0.449184,  -0.290884, 0.935852, -0.198918,  -0.973245, 0.014746, -0.229295,  -0.883864, 0.139334, -0.446509,  -0.894349, 0.013261, -0.447174,  -0.940238, 0.202386, -0.273847,  -0.883864, 0.139334, 0.446509,  -0.952320, 0.014402, 0.304760,  -0.894349, 0.013261, 0.447174,  -0.959873, 0.200796, 0.195768,  -0.722857, 0.526701, 0.447284,  -0.869986, 0.410146, 0.273688,  -0.832791, 0.328317, 0.445720,  -0.760151, 0.607497, 0.230473,  -0.889871, 0.412118, -0.195673,  -0.722858, 0.526700, -0.447284,  -0.832791, 0.328317, -0.445720,  -0.729589, 0.643963, -0.230241,  -0.953054, -0.126807, -0.274968,  -0.871736, -0.201442, -0.446651,  -0.947823, -0.251049, -0.196484,  -0.890166, -0.088586, -0.446941,  -0.972380, -0.125901, 0.196533,  -0.871736, -0.201442, 0.446651,  -0.890166, -0.088586, 0.446941,  -0.928482, -0.249709, 0.274895,  -0.902956, -0.382038, 0.196768,  -0.776215, -0.443768, 0.447839,  -0.835424, -0.319598, 0.447129,  -0.815650, -0.531011, 0.229657,  0.240037, -0.930683, -0.276065,  0.420906, -0.788150, -0.449063,  0.437973, -0.879862, -0.184451,  0.166184, -0.878520, -0.447867,  -0.559779, -0.781348, -0.275939,  -0.357242, -0.818937, -0.449133,  -0.395511, -0.905546, -0.153483,  -0.562486, -0.695226, -0.447515,  -0.576012, -0.793281, 0.197270,  -0.357242, -0.818937, 0.449133,  -0.562486, -0.695226, 0.447515,  -0.389434, -0.891647, 0.230884,  -0.687657, -0.571843, 0.447352,  -0.708080, -0.650394, 0.274972,  -0.708080, -0.650394, 0.274972,  -0.687657, -0.571843, 0.447352,  -0.687657, -0.571843, -0.447352,  -0.725511, -0.659544, -0.196560,  -0.725511, -0.659544, -0.196560,  -0.687657, -0.571843, -0.447352,  0.009246, -0.973234, -0.229630,  -0.137143, -0.883558, -0.447791,  0.008490, -0.894395, -0.447198,  -0.198659, -0.940408, -0.275984,  -0.137143, -0.883558, 0.447791,  0.009049, -0.952251, 0.305182,  0.008490, -0.894395, 0.447197,  -0.197061, -0.960334, 0.197295,  0.238166, -0.950957, 0.197378,  0.420906, -0.788150, 0.449063,  0.166184, -0.878520, 0.447867,  0.488393, -0.852907, 0.184451,  0.836382, -0.484008, -0.257296,  0.850385, -0.317397, -0.419648,  0.940604, -0.287044, -0.181302,  0.743656, -0.507847, -0.434818,  0.847769, -0.497443, 0.183953,  0.850385, -0.317397, 0.419647,  0.743656, -0.507847, 0.434818,  0.926729, -0.277209, 0.253631,  0.658341, -0.689343, 0.302314,  0.614488, -0.649888, 0.447270,  0.658341, -0.689343, 0.302314,  0.614488, -0.649888, 0.447270,  0.672913, -0.703868, -0.227502,  0.614489, -0.649887, -0.447270,  0.672913, -0.703868, -0.227502,  0.614489, -0.649887, -0.447270,  0.098341, 0.968268, -0.229753,  0.659163, 0.474301, -0.583560,  0.090377, 0.889850, -0.447213,  0.766091, 0.558194, -0.318628,  0.659163, 0.474302, 0.583560,  0.096217, 0.947353, 0.305393,  0.090377, 0.889850, 0.447213,  0.788303, 0.576430, 0.215191,  0.659163, 0.474302, 0.583560,  0.788303, 0.576430, 0.215191,  0.766091, 0.558194, -0.318628,  0.659163, 0.474301, -0.583560,  0.099068, 0.975422, 0.196819,  -0.493883, 0.651127, 0.576293,  0.090377, 0.889850, 0.447213,  -0.728889, 0.636356, 0.252531,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, -0.000000, 1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  -0.000001, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  -0.000001, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000,  0.000000, 0.000000, -1.000000
};

static const unsigned short CobjectIndices[NUM_C_OBJECT_INDEX] =
{
    0,1,2, 3,1,0, 4,5,6, 7,5,4, 8,9,10, 11,9,8, 12,13,14, 15,13,12, 16,17,18, 19,17,16, 20,21,22, 23,21,20, 24,25,26, 27,25,24, 26,23,20, 25,23,26, 28,29,30, 31,29,28, 28,27,31, 25,27,28, 23,16,21, 19,16,23, 23,28,19, 25,28,23, 19,30,17, 28,30,19, 32,33,34, 35,33,32, 36,37,38, 39,37,36, 38,35,32, 37,35,38, 40,41,42, 43,41,40, 40,39,43, 37,39,40, 35,12,33, 15,12,35, 35,40,15, 37,40,35, 15,42,13, 40,42,15, 44,45,46, 47,45,44, 48,49,50, 51,49,48, 33,52,34, 53,52,33, 53,54,52, 55,54,53, 56,12,14, 57,12,56, 57,33,12, 53,33,57, 48,46,51, 44,46,48, 55,57,58, 53,57,55, 59,57,56, 58,57,59, 60,61,62, 63,61,60, 64,65,66, 67,65,64, 51,66,49, 64,66,51, 64,62,67, 60,62,64, 64,46,60, 51,46,64, 63,46,45, 60,46,63, 68,69,70, 71,69,68, 67,68,65, 71,68,67, 71,8,69, 11,8,71, 71,62,11, 67,62,71, 9,62,61, 11,62,9, 72,73,74, 75,73,72, 76,77,78, 79,77,76, 80,81,82, 83,81,80, 70,84,85, 69,84,70, 85,83,80, 84,83,85, 86,10,87, 8,10,86, 86,69,8, 84,69,86, 83,76,81, 79,76,83, 83,86,79, 84,86,83, 79,87,77, 86,87,79, 88,89,90, 91,89,88, 92,93,94, 95,93,92, 96,92,94, 97,92,96, 92,90,95, 88,90,92, 92,98,88, 97,98,92, 88,99,91, 98,99,88, 100,101,102, 103,101,100, 95,104,93, 105,104,95, 100,74,103, 72,74,100, 105,90,106, 95,90,105, 107,90,89, 106,90,107, 108,109,110, 111,109,108, 112,113,114, 115,113,112, 103,116,101, 117,116,103, 118,112,114, 119,112,118, 120,74,73, 121,74,120, 121,103,74, 117,103,121, 112,110,115, 108,110,112, 112,122,108, 119,122,112, 108,123,111, 122,123,108, 124,125,126, 127,125,124, 128,129,130, 131,129,128, 115,132,113, 133,132,115, 131,124,129, 127,124,131, 133,110,134, 115,110,133, 135,110,109, 134,110,135, 136,137,138, 139,137,136, 130,139,136, 129,139,130, 139,4,137, 7,4,139, 139,124,7, 129,124,139, 7,126,5, 124,126,7, 140,141,142, 143,141,140, 144,145,146, 147,145,144, 148,149,150, 151,149,148, 152,153,154, 155,153,152, 156,157,158, 159,157,156, 157,155,152, 159,155,157, 160,161,162, 163,161,160, 163,156,161, 159,156,163, 155,148,153, 151,148,155, 155,163,151, 159,163,155, 151,160,149, 163,160,151, 164,165,166, 167,165,164, 153,168,154, 169,168,153, 169,164,168, 167,164,169, 170,148,150, 171,148,170, 171,153,148, 169,153,171, 167,144,165, 147,144,167, 167,171,147, 169,171,167, 145,171,170, 147,171,145, 172,173,174, 175,173,172, 176,177,178, 179,177,176, 180,181,182, 183,181,180, 182,179,176, 181,179,182, 184,185,186, 187,185,184, 184,183,187, 181,183,184, 179,172,177, 175,172,179, 179,184,175, 181,184,179, 175,186,173, 184,186,175, 188,189,190, 191,189,188, 192,193,194, 195,193,192, 177,194,178, 192,194,177, 192,190,195, 188,190,192, 192,172,188, 177,172,192, 191,172,174, 188,172,191, 196,197,198, 199,197,196, 195,198,193, 196,198,195, 196,142,199, 140,142,196, 196,190,140, 195,190,196, 143,190,189, 140,190,143, 200,201,202, 203,201,200, 204,205,206, 207,205,204, 208,209,210, 211,209,208, 199,212,197, 213,212,199, 214,210,215, 208,210,214, 216,142,141, 217,142,216, 217,199,142, 213,199,217, 208,206,211, 204,206,208, 208,218,204, 214,218,208, 207,218,219, 204,218,207, 220,221,222, 223,221,220, 224,225,226, 227,225,224, 209,227,224, 211,227,209, 227,220,225, 223,220,227, 227,206,223, 211,206,227, 223,205,221, 206,205,223, 228,229,230, 231,229,228, 225,230,226, 228,230,225, 228,202,231, 200,202,228, 228,220,200, 225,220,228, 203,220,222, 200,220,203, 232,233,234, 235,233,232, 236,237,238, 239,237,236, 229,240,241, 231,240,229, 242,238,243, 236,238,242, 244,201,245, 202,201,244, 244,231,202, 240,231,244, 236,234,239, 232,234,236, 236,246,232, 242,246,236, 235,246,247, 232,246,235, 248,249,250, 251,249,248, 252,253,254, 255,253,252, 239,256,237, 257,256,239, 255,248,253, 251,248,255, 257,234,258, 239,234,257, 259,234,233, 258,234,259, 260,261,262, 263,261,260, 253,262,254, 260,262,253, 260,2,263, 0,2,260, 260,248,0, 253,248,260, 3,248,250, 0,248,3, 264,265,266, 267,268,269, 270,271,272, 273,274,275, 264,273,265, 264,274,273, 276,274,264, 277,274,276, 277,278,274, 279,278,277, 280,278,279, 280,281,278, 282,281,280, 283,281,282, 283,284,281, 285,284,283, 285,286,284, 287,286,285, 287,288,286, 289,288,287, 289,290,288, 291,290,289, 291,292,290, 293,292,291, 293,294,292, 295,294,293, 295,296,294, 297,296,295, 297,298,296, 299,298,297, 300,298,299, 300,301,298, 302,301,300, 303,301,302, 303,304,301, 305,304,303, 305,306,304, 307,306,305, 308,306,307, 308,309,306, 310,309,308, 310,311,309, 312,311,310, 312,313,311, 314,313,312, 314,315,313, 316,315,314, 316,317,315, 268,317,316, 267,317,268, 267,270,317, 270,267,271, 318,319,320, 321,322,323, 324,325,326, 327,328,329, 328,319,318, 327,319,328, 327,330,319, 327,331,330, 332,331,327, 332,333,331, 332,334,333, 335,334,332, 335,336,334, 335,337,336, 338,337,335, 338,339,337, 340,339,338, 340,341,339, 342,341,340, 342,343,341, 344,343,342, 344,345,343, 346,345,344, 346,347,345, 348,347,346, 348,349,347, 350,349,348, 350,351,349, 352,351,350, 352,353,351, 352,354,353, 355,354,352, 355,356,354, 357,356,355, 357,358,356, 357,359,358, 360,359,357, 360,361,359, 360,362,361, 363,362,360, 363,364,362, 365,364,363, 365,366,364, 367,366,365, 367,368,366, 369,368,367, 369,370,368, 371,370,369, 371,321,370, 325,321,371, 324,321,325, 322,321,324
};


#endif // _C_OBJECT_H_
