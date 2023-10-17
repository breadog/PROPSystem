#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

void createUser(QString dirPath)
{
    QString dbName = "database.db";
    QString dbPath = dirPath + "./" + dbName;  // Use a relative path
//    qDebug() << dbPath;

    // Create database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (db.open()) {
        // Create table
        QSqlQuery query;
        qDebug() << "1234";
        if(query.exec("CREATE TABLE IF NOT EXISTS user (username varchar(20) primary key ,password varchar(20),cusNumber varchar(20))")){
            // Insert data
            qDebug() << "dbPath";
            QString username[51];
            QString password[51];
            QString cusNumber[51];
            for(int i = 1; i <= 9; i++){
                username[i] = "d0000" + QString::number(i);
                password[i] = "dc0000" + QString::number(i);
                cusNumber[i] = "yhh000" + QString::number(i);
            }
            for(int i = 10; i <= 50; i++){
                username[i] = "d000" + QString::number(i);
                password[i] = "dc000" + QString::number(i);
                cusNumber[i] = "yhh00" + QString::number(i);
            }

            for(int i = 1; i <= 50; i++){
                QString insertQuery = "INSERT INTO user (username, password, cusNumber) VALUES ('" + username[i] + "','" + password[i] + "','" + cusNumber[i] + "')";
                query.exec(insertQuery);
            }

        }
        // Close database connection
        db.close();
//        qDebug() << "Data inserted successfully.";
    } else {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败：" + db.lastError().text());
    }
}

