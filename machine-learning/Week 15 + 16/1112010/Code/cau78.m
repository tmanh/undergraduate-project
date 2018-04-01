%Truong Minh Anh - 1112010
%truongminhanh93.it@gmail.com
%----------------------------

function cau78(features_in)
    disp('Ket qua thi nghiem voi Q = 2');
    
    result = zeros(5,1);
    err_cv = zeros(5,1);
    
    for i = 1:100
        [err_vali vote] = Q2(features_in);
        err_cv = err_cv + err_vali;
        result(vote) = result(vote) + 1;
    end
    
    err_cv = err_cv ./ 100;
    [tmp index] = max(result);
    
    disp('So lan duoc chon cua cac C(tu 0.0001->1)');
    disp(result);
    disp('Gia tri do loi trung binh thap nhat:');
    disp(err_cv(index));
end

function [err_vali vote] = Q2(features_in)
    %khoi tao nhan training set
    lenght_in = length(features_in);
    tmp_ones_in = ones(1, lenght_in);
    
    %dem so phan tu 1 va 5
    tmp = (features_in(:, 1) == 1) | (features_in(:, 1) == 5);
    number_of_in = tmp_ones_in * tmp;
    
    %khoi tao nhan training set va lay tap du lieu
    in_label = ones(number_of_in, 1);
    in = ones(number_of_in, 2);
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

    %partition
    mat_vali_index = initializeValiIndexMatrix(round(length(in) / 10), 10);
    
    %khoi tao bien luu tru do loi cac tap vali
    err_vali_vali1 = zeros(10, 1);
    err_vali_vali2 = zeros(10, 1);
    err_vali_vali3 = zeros(10, 1);
    err_vali_vali4 = zeros(10, 1);
    err_vali_vali5 = zeros(10, 1);
    err_vali = zeros(5, 1);
    rows = round(length(in) / 10);
    ones_mat_vali = ones(1, round(length(in) / 10));
    
    for i = 1:10
        %create subtrain, subvali
        [train vali train_label vali_label] = initializeSubMatrix(round(length(in) / 10), mat_vali_index(:, i), in, in_label);

        %train
        model1 = svmtrain(train_label(:, 1), train, '-t 1 -c 0.0001 -d 2 -q');
        model2 = svmtrain(train_label(:, 1), train, '-t 1 -c 0.001 -d 2 -q');
        model3 = svmtrain(train_label(:, 1), train, '-t 1 -c 0.01 -d 2 -q');
        model4 = svmtrain(train_label(:, 1), train, '-t 1 -c 0.1 -d 2 -q');
        model5 = svmtrain(train_label(:, 1), train, '-t 1 -c 1 -d 2 -q');

        %phan lop In
        [predicted_label1] = svmpredict(vali_label, vali, model1, '-q');
        [predicted_label2] = svmpredict(vali_label, vali, model2, '-q');
        [predicted_label3] = svmpredict(vali_label, vali, model3, '-q');
        [predicted_label4] = svmpredict(vali_label, vali, model4, '-q');
        [predicted_label5] = svmpredict(vali_label, vali, model5, '-q');

        %tinh do loi
        err_label = vali_label(:) ~= predicted_label1(:);
        err_vali_vali1(i) = ones_mat_vali * err_label;
        err_vali_vali1(i) = err_vali_vali1(i) / rows;
        
        err_label = vali_label(:) ~= predicted_label2(:);
        err_vali_vali2(i) = ones_mat_vali * err_label;
        err_vali_vali2(i) = err_vali_vali2(i) / rows;
        
        err_label = vali_label(:) ~= predicted_label3(:);
        err_vali_vali3(i) = ones_mat_vali * err_label;
        err_vali_vali3(i) = err_vali_vali3(i) / rows;
        
        err_label = vali_label(:) ~= predicted_label4(:);
        err_vali_vali4(i) = ones_mat_vali * err_label;
        err_vali_vali4(i) = err_vali_vali4(i) / rows;
        
        err_label = vali_label(:) ~= predicted_label5(:);
        err_vali_vali5(i) = ones_mat_vali * err_label;
        err_vali_vali5(i) = err_vali_vali5(i) / rows;
    end
    
    %get err_vali
    for i = 1:10
        err_vali(1) = err_vali(1) + err_vali_vali1(i);
    end
    err_vali(1) = err_vali(1) / 10;
    
    for i = 1:10
        err_vali(2) = err_vali(2) + err_vali_vali2(i);
    end
    err_vali(2) = err_vali(2) / 10;
    
    for i = 1:10
        err_vali(3) = err_vali(3) + err_vali_vali3(i);
    end
    err_vali(3) = err_vali(3) / 10;
    
    for i = 1:10
        err_vali(4) = err_vali(4) + err_vali_vali4(i);
    end
    err_vali(4) = err_vali(4) / 10;
    
    for i = 1:10
        err_vali(5) = err_vali(5) + err_vali_vali5(i);
    end
    err_vali(5) = err_vali(5) / 10;
    
    [tmp vote] = min(err_vali);
end

function [result_index] = initializeValiIndexMatrix(rows, cols)
    result_index = zeros(rows, cols);
    
    mat_length = rows * 10;
    
    count = zeros(10,1);
    
    for k = 1:mat_length
        while 1
            index = round(unifrnd(1,cols));
            
            if(count(index) < rows)
                count(index) = count(index) + 1;
                    
                result_index(count(index), index) = k;
                break;
            end
        end
    end
end

function [train vali train_label vali_label] = initializeSubMatrix(rows, mat_vali_index, in, in_label)
    mat_length = length(in);

    train = zeros(mat_length - rows, 2);
    train_label = zeros(mat_length - rows, 1);
    vali = zeros(rows, 2);
    vali_label = zeros(rows, 1);
    
    count = zeros(10,1);
    
    i = 1; j = 1;
    for k = 1:mat_length
        if i <= rows && k == mat_vali_index(i)
            vali(i, 1) = in(k, 1); vali(i, 2) = in(k, 2);
            vali_label(i) = in_label(k);
            i = i + 1;
        else
            train(j, 1) = in(k, 1); train(j, 2) = in(k, 2);
            train_label(j) = in_label(k);
            j = j + 1;
        end
    end
end