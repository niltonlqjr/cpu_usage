CPU_USAGE_EXEC=./cpu_usage

n_flags=0

while getopts c:e:i:o: flag
do
    case "${flag}" in
        c)
            command_line=${OPTARG}
            n_flags=$((n_flags+1));;
        e)
            exec_name=${OPTARG}
            n_flags=$((n_flags+1));;
        i) 
            interval=${OPTARG}
            n_flags=$((n_flags+1));;
        o) 
            output_file=${OPTARG}
            n_flags=$((n_flags+1));;
    esac
done

if [ $n_flags -eq 4 ]
then
    echo "Command line: ${command_line}";
    echo "Executable name: ${exec_name}";
    echo "Interval (milli seconds): ${interval}";
    echo "Output file: ${output_file}";

    if [ -f ${output_file} ]
    then
        echo "${output_file} already exist, moving to ${output_file}.bak"
        mv ${output_file} ${output_file}.bak
    fi

    ${CPU_USAGE_EXEC} ${exec_name} ${interval} ${output_file} &

    PID_LOAD=$!

    ${command_line}

    kill ${PID_LOAD}
else
    echo "Invalid flags:"
    echo "$0 -c <command_line> -e <executable name> -i <interval between ps command> -o <output file>"
fi