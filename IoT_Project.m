clc;
clear;
close all;

readChId=1925613; % Channel ID
readKey="DID12AN6KRV5DXKE"; % Read API Key

[weatherData,timeStamp]=thingSpeakRead(readChId,'Fields',1,'Numpoints',3000,'Readkey',readKey);

% Task-1 : plotting raw temp
figure;
plot(timeStamp,weatherData);
xlabel('Time');
ylabel('Temp (°C)');
legend('Temperature');
title('Raw Temp Data', 'fontsize',14,'fontweight','bold');
grid on;

%Task-2 - min & max of temp
fprintf('min temp is %d\n', min(weatherData));
fprintf('max temp is %d\n', max(weatherData)); 

%Task-3 - avg of temp
temp_sum = sum(weatherData);
avg_temp = temp_sum/length(weatherData);
fprintf('avg temp is %d\n', avg_temp);

% %Task-4 : histogram of temperature
figure;
histogram(weatherData);

% Task-5 : cleaning data (considering temperature which is less than 50 deg C) and plotting
cleanWeatherData = weatherData;
cleanTimeStamps = timeStamp;

l = length(weatherData);

for i = 1:l
    if (weatherData(i) > 50)
        cleanWeatherData(i) = sum(cleanWeatherData)/length(cleanWeatherData);
    end
end

% Task-5 : plotting cleaned data
display(cleanWeatherData, 'Cleaned data');
cleanWeatherData
figure;
histogram(cleanWeatherData);
figure;
plot(cleanTimeStamps,cleanWeatherData);
xlabel('Time');
ylabel('Temp (°C)');
title('Cleaned Temp Data', 'fontsize',14,'fontweight','bold');
grid on;