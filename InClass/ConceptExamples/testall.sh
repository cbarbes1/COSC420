mpicc -o gather gather.c
mpicc -o allgather allgather.c
mpicc -o broadcast broadcast.c
mpicc -o alltoall alltoall.c
mpicc -o reduce reduce.c
mpicc -o allreduce allreduce.c
mpicc -o scan scan.c
mpicc -o rs reducescatter.c




echo "Broadcast:" >> output.txt
mpirun broadcast 8 >> output.txt
echo "allgather:" >> output.txt
mpirun allgather >> output.txt
echo "gather:" >> output.txt
mpirun gather >> output.txt
echo "alltoall:" >> output.txt
mpirun alltoall >> output.txt
echo "reduce:" >> output.txt
mpirun reduce >> output.txt
echo "allreduce:" >> output.txt
mpirun allreduce >> output.txt
echo "scan:" >> output.txt
mpirun scan >> output.txt
echo "reduce scatter:" >> output.txt
mpirun rs >> output.txt


rm gather allgather broadcast alltoall reduce allreduce scan rs