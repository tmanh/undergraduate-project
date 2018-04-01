%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com

%1: mat ngua, 0: mat xap

function [vmin, v1, vrand] = HoeffdingCoins()

min_pos = -1;        %vi tri dong tien co so mat ngua nho nhat
min_value = -1;      %so mat ngua nho nhat

count_min = 0;  %so mat ngua cua dong tien co so mat ngua it nhat
count_1 = 0;    %so dong tien cua dong tien 1
count_rand = 0; %so dong tien cua dong tien duoc random

for i = 1:100000
    coins = round(unifrnd(0,1,1000,10));   %ma tran chua ket qua random tung dong xu
    t = ones(10,1);                         %ma tran luu tham gia vao viec tinh tong so mat ngua
    
    sum_coins = coins * t;                  %ma tran luu tong so mat ngua cua cac dong tien
    
    [new_min_value, new_min_pos] = min(sum_coins);
    
    if(new_min_value ~= min_value)
        min_pos = new_min_pos;
    end
       
    rand_pos = round(unifrnd(1,1000,1,1));
    
    count_min = count_min + new_min_value;
    count_1 = count_1 + sum_coins(1);
    count_rand = count_rand + sum_coins(rand_pos);
end

vmin = count_min / 10 / 100000;
v1 = count_1 / 10 / 100000;
vrand = count_rand / 10 / 100000;
end