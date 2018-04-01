%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function cau910(features_in, features_out)
%model0 model1, model2, model3, model4, err_in, err_out
    disp('Ket qua thi nghiem voi Q = 2');
    [err_in, err_out] = RBF(features_in, features_out);
    disp('Thong tin do loi Ein theo thu tu tang dan cua C(tu 0.01 den 10^6):');
    disp(err_in);
    disp('Thong tin do loi Eout theo thu tu tang dan cua C(tu 0.01 den 10^6):');
    disp(err_out);
end

function [err_in, err_out] = RBF(features_in, features_out)
    %khoi tao nhan training set
    lenght_in = length(features_in);
    lenght_out = length(features_out);
    tmp_ones_in = ones(1, lenght_in);
    tmp_ones_out = ones(1, lenght_out);
    
    %dem so phan tu 1 va 5
    tmp = (features_in(:, 1) == 1) | (features_in(:, 1) == 5);
    number_of_in = tmp_ones_in * tmp;
    
    %khoi tao nhan training set va lay tap du lieu
    in_label = ones(number_of_in, 1);
    in = ones(number_of_in, 2);
    ones_mat_in = ones(1, number_of_in);
    k = 1;
    
	for j = 1:lenght_in
        if(features_in(j, 1) == 5)
            in_label(k) = 1;
            in(k, 1) = features_in(j, 2); in(k, 2) = features_in(j, 3);
            k = k + 1;
        elseif(features_in(j, 1) == 1)
            in_label(k) = 0;
            in(k, 1) = features_in(j, 2); in(k, 2) = features_in(j, 3);
            k = k + 1;
        end
	end
    
    %dem so phan tu 1 va 5
    tmp = (features_out(:, 1) == 1) | (features_out(:, 1) == 5);
    number_of_out = tmp_ones_out * tmp;

    %khoi tao nhan test set
    out_label = ones(number_of_out, 1);
    out = ones(number_of_out, 2);
    ones_mat_out = ones(1, number_of_out);
    k = 1;
    
	for j = 1:lenght_out
        if(features_out(j, 1) == 5)
            out_label(k) = 1;
            out(k, 1) = features_out(j, 2); out(k, 2) = features_out(j, 3);
            k = k + 1;
        elseif(features_out(j, 1) == 1)
            out_label(k) = 0;
            out(k, 1) = features_out(j, 2); out(k, 2) = features_out(j, 3);
            k = k + 1;  
        end
    end

    model0 = svmtrain(in_label(:, 1), in, '-t 2 -c 0.001 -g 1 -q');
    model1 = svmtrain(in_label(:, 1), in, '-t 2 -c 1 -g 1 -q');
    model2 = svmtrain(in_label(:, 1), in, '-t 2 -c 100 -g 1 -q');
    model3 = svmtrain(in_label(:, 1), in, '-t 2 -c 10000 -g 1 -q');
    model4 = svmtrain(in_label(:, 1), in, '-t 2 -c 1000000 -g 1 -q');
    
    %phan lop In
    [predicted_label0] = svmpredict(in_label, in, model0, '-q');
    [predicted_label1] = svmpredict(in_label, in, model1, '-q');
    [predicted_label2] = svmpredict(in_label, in, model2, '-q');
    [predicted_label3] = svmpredict(in_label, in, model3, '-q');
    [predicted_label4] = svmpredict(in_label, in, model4, '-q');

    %tinh do loi
    err_label = in_label(:) ~= predicted_label0(:);
    err_in0 = ones_mat_in * err_label;
    err_in0 = err_in0 / number_of_in;
    err_label = in_label(:) ~= predicted_label1(:);
    err_in1 = ones_mat_in * err_label;
    err_in1 = err_in1 / number_of_in;
    err_label = in_label(:) ~= predicted_label2(:);
    err_in2 = ones_mat_in * err_label;
    err_in2 = err_in2 / number_of_in;
    err_label = in_label(:) ~= predicted_label3(:);
    err_in3 = ones_mat_in * err_label;
    err_in3 = err_in3 / number_of_in;
    err_label = in_label(:) ~= predicted_label4(:);
    err_in4 = ones_mat_in * err_label;
    err_in4 = err_in4 / number_of_in;
    
    err_in = [err_in0 err_in1 err_in2 err_in3 err_in4];
    
    %phan lop Out
    [predicted_label0] = svmpredict(out_label, out, model0, '-q');
    [predicted_label1] = svmpredict(out_label, out, model1, '-q');
    [predicted_label2] = svmpredict(out_label, out, model2, '-q');
    [predicted_label3] = svmpredict(out_label, out, model3, '-q');
    [predicted_label4] = svmpredict(out_label, out, model4, '-q');
    
    %tinh do loi
    err_label = out_label(:) ~= predicted_label0(:);
    err_out0 = ones_mat_out * err_label;
    err_out0 = err_out0 / number_of_in;
    err_label = out_label(:) ~= predicted_label1(:);
    err_out1 = ones_mat_out * err_label;
    err_out1 = err_out1 / number_of_in;
    err_label = out_label(:) ~= predicted_label2(:);
    err_out2 = ones_mat_out * err_label;
    err_out2 = err_out2 / number_of_in;
    err_label = out_label(:) ~= predicted_label3(:);
    err_out3 = ones_mat_out * err_label;
    err_out3 = err_out3 / number_of_in;
    err_label = out_label(:) ~= predicted_label4(:);
    err_out4 = ones_mat_out * err_label;
    err_out4 = err_out4 / number_of_in;
    
    err_out = [err_out0 err_out1 err_out2 err_out3 err_out4];
end