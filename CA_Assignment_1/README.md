1)Sorted Array using Quick sort

![2aa6bdf5-815a-4f74-83f1-66b084296f7d (1)](https://github.com/user-attachments/assets/c57cb835-38a7-4b0e-94a1-6b450976d356)

2)Profiling Output using gprof

Commands Used:

1)gcc -o quick -pg quick.c
2)./quick
3)gprof quick gmon.out > analysis.txt
4)cat analysis.txt

![38ba7d84-7f71-4b8d-b221-3607b2e969ae (1)](https://github.com/user-attachments/assets/1049129c-10cc-418f-9e5c-791843b561ed)

3)Visual of Profiling
Commands Used: 1) gprof2dot -f prof analysis.txt > call_graph.dot 
               2) dot -Tpng -o call_graph.png call_graph.dot
               
![analysis](https://github.com/user-attachments/assets/8fcf253c-dd9d-48b7-be83-600646830cab)

