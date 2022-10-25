curr_work_path=`pwd`
build_dir_path="$curr_work_path/build"
echo ${build_dir_path}

rm -r -f ${build_dir_path}
mkdir ${build_dir_path}

cd ${build_dir_path}
curr_work_path=`pwd`
echo ${curr_work_path}

cmake ..
make

# ${build_dir_path}/bin/adjust_array

bin_path=${build_dir_path}/bin/
for file in ${bin_path}/*
do 
    if test -f ${file}
    then
        ${file}
    fi
done