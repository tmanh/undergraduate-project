% Linear Regression Example
% Truong Minh Anh - truongminhanh93.it@gmail.com
% -------------------------
function [result] = linear_regression(data, normal_mat)
% -----------------------------------------------
% clear screen
% -----------------------------------------------
clc;
% -----------------------------------------------
% initialize const
% -----------------------------------------------
exp = 2.71828182846;
eta = 0.1;
err = 0.0000001;
% -----------------------------------------------
% load data
% -----------------------------------------------
data_length = size(data,2);     % number of columns
N = size(data,1);               % number of rows
Y = [data(:,data_length)]';     % get target class
X = [data(:,1:data_length-1) ones(N,1)]';% get sample
flag_end = 0;                   % initialize flag for terminate loop of gradient descent
% -----------------------------------------------
% normalize data
% -----------------------------------------------
for i = 1:data_length-1
    if(normal_mat(i) == 1)
        Mean = mean(X(i,:));
        Var = var(X(i,:));
        X(i,:) = (X(i,:) - Mean)/sqrt(Var);
    end
end
% -----------------------------------------------
% Linear Regression Algorithm by Gradient Descent
% -----------------------------------------------
% 1. Initialize the weights at t = 0
% 2. for t = 0,1,2,... do
%   2.1. Compute gradient: delta_err = -1/N*sum(y_n*x_n/(1+e^(y_n*B'*x_n)))
%   2.2. Update weights: B = B - eta*delta_err
%   2.3. Iterate until the weights change not much
% 3. Return final weights
% 4. Compute out class
% -----------------------------------------------
% 1. Initialize the weights at t = 0
% -----------------------------------------------
B = rand(data_length,1);
% -----------------------------------------------
% 2. for t = 0,1,2,... do
% -----------------------------------------------
while flag_end == 0
% 2.1. Compute gradient: delta_err = -1/N*sigma(y_n*x_n/(1+e^(y_n*B'*x_n)))
% -----------------------------------------------
yBx = Y.*(B'*X);                % compute matrix of all y_n*B'*x_n
O = ones(N,1);                  % initialize matrix Nx1 with all value equal 1
EXP = exp * O;                  % initialize matrix Nx1 with all value equal exp
denominator = O + EXP.^(yBx');  % compute matrix of all (1+e^(y_n*B'*x_n))
% compute matrix of all x_n/(1+e^(y_n*B'*x_n)
for i = 1:data_length
    XdivDenominator(:,i) = (X(i,:)')./denominator;
end
delta_err = -Y*XdivDenominator/N;% compute delta_err = -1/N*sigma(y_n*x_n/(1+e^(y_n*B'*x_n)))
% -----------------------------------------------
% 2.2. Update weights: B = B - eta*delta_err
% -----------------------------------------------
ETA = eta * ones(data_length,1);     % initialize matrix Nx1 with all value equal eta
B_new = B - ETA .* delta_err';       % update B
% -----------------------------------------------
% 2.3. Iterate until the weights change not much
% -----------------------------------------------
err_B = (B_new - B)'*(B_new - B); %compute difference between B_new and B
if(err_B < err)
    flag_end = 1;
end
B = B_new;
end
% -----------------------------------------------
% 3. Return final weights
% -----------------------------------------------
final_B = B;
% -----------------------------------------------
% 4. Initialize the weights at t = 0
% -----------------------------------------------
z = final_B'*X;
out_percent = O ./ (O + EXP .^ -z');
for i = 1:N
    index(i,1) = i;
    if(out_percent(i) >= 0.5)
        out_class(i,1) = 1;
    else
        out_class(i,1) = -1;
    end
end
result = [index out_percent out_class Y'];
end
