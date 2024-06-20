% Read data from quicksort.txt
quicksortData = readmatrix('quicksort.txt', 'Delimiter', '\t');

% Read data from insertsort.txt
insertsortData = readmatrix('insertsort.txt', 'Delimiter', '\t');

% Extract lengths and nanoseconds
quicksortLengths = quicksortData(:, 1);
quicksortTimes = quicksortData(:, 2);

insertsortLengths = insertsortData(:, 1);
insertsortTimes = insertsortData(:, 2);

% Determine n0 as the length from which quicksort is always faster than insertion sort
n0 = max(quicksortLengths); % Start with the maximum length
for i = 1:length(quicksortLengths)
    if all(quicksortTimes(i:end) < insertsortTimes(i:end))
        n0 = quicksortLengths(i);
        break;
    end
end
xLimit = 2 * n0;

quicksortLengths = quicksortLengths(quicksortLengths <= xLimit);
quicksortTimes = quicksortTimes(quicksortLengths <= xLimit);

insertsortLengths = insertsortLengths(insertsortLengths <= xLimit);
insertsortTimes = insertsortTimes(insertsortLengths <= xLimit);

% Find the maximum time to set the y-axis scale
maxTime = max(max(quicksortTimes), max(insertsortTimes));

% Plot the data
figure;
hold on;

% Plot the quicksort data
plot(quicksortLengths, quicksortTimes, '-o', 'DisplayName', 'Quicksort');

% Plot the insertsort data
plot(insertsortLengths, insertsortTimes, '-x', 'DisplayName', 'Insertsort');

% Add a vertical line at n0
xline(n0, '--r', 'DisplayName', 'n0');

% Add text label for n0
text(n0, maxTime, sprintf('n0 = %d', n0), 'VerticalAlignment', 'bottom', 'HorizontalAlignment', 'right', 'Color', 'r');

% Set graph properties
xlabel('Vector Length');
ylabel('Time (nanoseconds)');
title('Quicksort vs Insertsort Performance');
xlim([1, xLimit]);
ylim([0, maxTime * 1.1]);
legend show;

grid on;
hold off;

% Save the plot as a PNG file
saveas(gcf, 'sorting_performance_comparison.png');
