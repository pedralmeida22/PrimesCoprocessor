# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\PrimesCount\vitis_workspace\primesCountCop\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\PrimesCount\vitis_workspace\primesCountCop\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {primesCountCop}\
-hw {C:\PrimesCount\primesCount\primesCount.xsa}\
-fsbl-target {psu_cortexa53_0} -out {C:/PrimesCount/vitis_workspace}

platform write
domain create -name {standalone_microblaze_0} -display-name {standalone_microblaze_0} -os {standalone} -proc {microblaze_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {primesCountCop}
platform generate -quick
platform generate
bsp reload
platform generate -domains 
platform config -updatehw {C:/PrimesCount/primesCount/primesCount.xsa}
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform active {primesCountCop}
platform config -updatehw {C:/PrimesCount/primesCount/primesCount.xsa}
platform clean
platform generate
platform clean
platform generate
platform generate -domains standalone_microblaze_0 
