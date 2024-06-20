clear;clc;close all;

data=readmatrix('quicksort.txt', 'Delimiter', '\t');
x=data(1);
quicksort_y=data(2);

data=readmatrix('mergesort.txt','Delimiter','\t');
mergesort_y=data(2);

data=readmatrix('heapsort.txt','Delimiter','\t');
heapsort_y=data(2);

fid=fopen('shellsort_2n.txt');
data=readmatrix('shellsort_2n.txt','Delimiter','\t');
shellsort_y=data(2);

figure;
title('sorting algorithms');
xlabel('n [-]');
ylabel('t [s]');
hold on;
plot(x,quicksort_y, '-x', 'DisplayName', 'quicksort');
plot(x,mergesort_y, '-x', 'DisplayName', 'mergesort');
plot(x,heapsort_y, '-x', 'DisplayName', 'heapsort');
plot(x,shellsort_y, '-x', 'DisplayName', 'shellsort');
xlim([1, x]);
ylim([1, max(max(max(quicksort_y), max(mergesort_y)), max(max(heapsort_y), max(shellsort_y)))]);
legend show;
grid on;
hold off;
