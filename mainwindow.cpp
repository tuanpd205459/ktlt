#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

      devserial = new QSerialPort(this);

      /* Create Object the Class comserial to manipulate read/write of the my way */
      procSerial = new comserial(devserial);


          serialBuffer = "";
          parsed_data = "";
          temperature_value = "";
            humidity_value ="";

      QStringList DispSeriais = procSerial->ConnectDevices();
      ui->comboBoxPort->addItems(DispSeriais);


      if(DispSeriais.length() > 0) {
          ui->pushButtonConnect->setEnabled(true);
          ui->textEditGetData->append("###  Cổng nối tiếp đã sẵn sàng để sử dụng.");
      }
      else { ui->textEditGetData->append("### Không phát hiện thấy cổng nối tiếp!");
      }





      connect(devserial, SIGNAL(readyRead()), this, SLOT(readSerial()));
  }




MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButtonSendData_clicked()
{

    QString Cmd = ui->lineEditCmd->text()+ "\n";
    qDebug() << "Output: " << Cmd << endl;
    WriteData(Cmd.toUtf8());

}

void MainWindow::ReadData() {
    QByteArray data = devserial->readLine();
    QString receivedData = QString::fromUtf8(data); // Chuyển đổi từ QByteArray sang QString sử dụng mã hóa UTF-8


//  QString receivedData = procSerial->Read();

    qDebug() << "input: " << receivedData << endl;
    ui->textEditGetData->append(receivedData);

    qDebug() << "ReadData() is called when data is available.";

    //Kiểm tra dữ liệu từ cổng Serial
   qDebug() << "Serial data received: " << procSerial->Read();
   updateTemperature(receivedData);

}

void MainWindow::WriteData(const QByteArray data)
{
    procSerial->Write(data);
}

void MainWindow::on_pushButtonConnect_clicked()
{   bool statusOpenSerial;
    statusOpenSerial = procSerial->ConnectCom(ui->comboBoxPort->currentText());
    if(statusOpenSerial){
        ui->textEditGetData->append("Ket noi port thanh cong");
    }
    else {
        ui->textEditGetData->append("ket noi that bai");
    }
}


void MainWindow::on_pushButtonDisconnect_clicked()
{

        bool statusCloseSerial;


        statusCloseSerial = procSerial->Disconnect();


        if (statusCloseSerial) {

            ui->textEditGetData->append("### NGat ket noi thanh cong!");
        }
        else {
            ui->textEditGetData->append("###Ngawt ket noi that bai.");
        }

}

void MainWindow::updateTemperature(QString sensor_reading)
{
    //  update the value displayed on the lcdNumber
    ui->lcdNumberTemperature->display(sensor_reading);
}
void MainWindow::updateHumidity(QString sensor_reading)
{
    //  update the value displayed on the lcdNumber
    ui->lcdNumberHumidity->display(sensor_reading);
}

void MainWindow::readSerial()
{

    QStringList buffer_split = serialBuffer.split("\r\n"); //  split the serialBuffer string, parsing with '\r\n' as the separator

    if(buffer_split.length() < 3){

        serialData = devserial->readAll();
        serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
        qDebug() << serialBuffer;
        serialData.clear();
    }else{

        serialBuffer = "";
        qDebug() << buffer_split << "\n";
        temperature_value = buffer_split[1];
        humidity_value = buffer_split[0];

        qDebug() << "Temperature: " <<  temperature_value << "\n";
        qDebug() << "Humidity: " <<  humidity_value << "\n";

        MainWindow::updateTemperature(temperature_value);
        MainWindow::updateHumidity(humidity_value);

    }

}



void MainWindow::on_pushButtonTurnOn_clicked()
{
    if (devserial->isOpen() && devserial->isWritable()) {
        // Gửi dữ liệu xuống Arduino
        QString dataToSend = "1";
        QByteArray sendData = dataToSend.toUtf8(); // Chuyển đổi QString sang QByteArray
        qint64 bytesWritten = devserial->write(sendData);
        qDebug()<< "Send Data "<<sendData;
        if (bytesWritten == -1) {
            // Xử lý lỗi: Không gửi được dữ liệu
            qDebug() << "Error writing data to serial port";
        } else if (bytesWritten < sendData.size()) {
            // Xử lý lỗi: Chưa gửi được toàn bộ dữ liệu
            qDebug() << "Not all data has been written to serial port";
        } else {
            // Gửi dữ liệu thành công
            devserial->waitForBytesWritten(1000); // Đợi cho đến khi dữ liệu được gửi đi
        }
    } else {
        // Xử lý lỗi: Serial port không mở hoặc không ghi được
        qDebug() << "Serial port is not open or not writable";
    }
}


void MainWindow::on_pushButtonTurnOff_clicked()
{
    if (devserial->isOpen() && devserial->isWritable()) {
        // Gửi dữ liệu xuống Arduino
        QString dataToSend = "0";
        QByteArray sendData = dataToSend.toUtf8(); // Chuyển đổi QString sang QByteArray
        qint64 bytesWritten = devserial->write(sendData);
        qDebug()<< "Send Data "<<sendData;
        if (bytesWritten == -1) {
            // Xử lý lỗi: Không gửi được dữ liệu
            qDebug() << "Error writing data to serial port";
        } else if (bytesWritten < sendData.size()) {
            // Xử lý lỗi: Chưa gửi được toàn bộ dữ liệu
            qDebug() << "Not all data has been written to serial port";
        } else {
            // Gửi dữ liệu thành công
            devserial->waitForBytesWritten(1000); // Đợi cho đến khi dữ liệu được gửi đi
        }
    } else {
        // Xử lý lỗi: Serial port không mở hoặc không ghi được
        qDebug() << "Serial port is not open or not writable";
    }
}

