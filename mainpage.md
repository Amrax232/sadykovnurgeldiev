# Лабораторная работа по дисциплине "Технологии и методы программирования"

**Тема 19: Реализация алгоритмов**  
**Группа: 241-351**

## Реализованные алгоритмы:
1. **Triple DES** - шифрование конфиденциальных данных
2. **MD5** - хеширование паролей пользователей
3. **Метод секущих** - численное решение уравнений
4. **Проверка циклов в графе** - теория графов

## Пример использования MD5:
```cpp
#include <QCryptographicHash>
#include <QDebug>

QString md5Hash(const QString& password) {
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(password.toUtf8());
    return QString(hash.result().toHex());
}

int main() {
    QString password = "securePassword123";
    qDebug() << "MD5 Hash:" << md5Hash(password);
    return 0;
}