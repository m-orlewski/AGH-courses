USE AdventureWorks2008

CREATE TABLE Employee
(ID integer NOT NULL IDENTITY(1,1),
FirstName VARCHAR(50),
LastName VARCHAR(50),
Email VARCHAR(50),
AddressLine VARCHAR(50),
Salary MONEY,
ModifyDate datetime,
CONSTRAINT[PK_Vlab.Employee_ID] PRIMARY KEY CLUSTERED
([ID] ASC)
WITH
(PAD_INDEX=OFF,STATISTICS_NORECOMPUTE=OFF,IGNORE_DUP_KEY=OFF,ALLOW_ROW_LOCKS=ON,ALLOW_PAGE_LOCKS=ON))
GO

WITH lastRate(id,ratedate)
AS 
(SELECT BusinessEntityID,MAX(RateChangeDate)
FROM HumanResources.EmployeePayHistory GROUP BY BusinessEntityID)
INSERT INTO Employee(FirstName, LastName, Email, AddressLine, Salary )
SELECT FirstName, LastName, EA.EmailAddress, A.AddressLine1, Pay.Rate 
FROM Person.EmailAddress EA JOIN Person.BusinessEntity BE ON EA.BusinessEntityID =BE.BusinessEntityID
JOIN Person.BusinessEntityAddress BEA ON BEA.BusinessEntityID =BE.BusinessEntityID
JOIN Person.Address A ON BEA.AddressID =A.AddressID
JOIN Person.Person P ON P.BusinessEntityID =BE.BusinessEntityID
JOIN Person.PersonPhone Phone ON Phone.BusinessEntityID =P.BusinessEntityID
JOIN HumanResources.Employee Emp ON P.BusinessEntityID =Emp.BusinessEntityID
JOIN HumanResources.EmployeePayHistory Pay ON Emp.BusinessEntityID =Pay.BusinessEntityID
JOIN lastRate Lrate ON Lrate.id =Pay.BusinessEntityID
WHERE Lrate.ratedate =Pay.RateChangeDate

--zad 1
CREATE TRIGGER employeeMinSalary ON Employee
AFTER INSERT, UPDATE NOT FOR REPLICATION AS
BEGIN
	IF (SELECT Salary FROM inserted) < 10
	BEGIN
		RAISERROR ('Salary musi byc wieksze lub rowne 10', 10, 1);
		ROLLBACK TRANSACTION;
	END;
	
	IF UPDATE ([Salary])
	BEGIN
		IF (SELECT [inserted].[Salary] FROM [inserted]) < (SELECT [deleted].[Salary] FROM [deleted]) OR
			(SELECT [inserted].[Salary] FROM [inserted]) < 10
		BEGIN
			RAISERROR ('Nowe Salary musi byc wieksze od starej i od 10', 10, 1);
			ROLLBACK TRANSACTION;
		END;
	END;
END;
GO

--zad 2
SET NOCOUNT ON;

DECLARE @id INT, @name NVARCHAR(80), @message VARCHAR(80),
@total MONEY, @sid INT;

DECLARE my_product_cursor CURSOR FOR
SELECT ProductID, Name FROM Production.Product;

OPEN my_product_cursor

FETCH NEXT FROM my_product_cursor INTO @id, @name

WHILE @@FETCH_STATUS = 0
BEGIN
	PRINT ' '
	SELECT @message = '----- Produkty: ' + @name
	PRINT @message

	DECLARE my_sales_cursor CURSOR FOR
	SELECT sd.SalesOrderID, sh.SubTotal
	FROM Sales.SalesOrderDetail sd
	JOIN Sales.SalesOrderHeader sh ON sh.SalesOrderID = sd.SalesOrderID
	WHERE sd.ProductID = @id;

	OPEN my_sales_cursor
	FETCH NEXT FROM my_sales_cursor INTO @sid, @total;

	WHILE @@FETCH_STATUS = 0
	BEGIN
		PRINT ' '
		SELECT @message = 'Sale ID: ' + convert(varchar(20), @sid)
		PRINT @message
		SELECT @message = 'Sale Total: ' + convert(varchar(40), @total, 1)
		PRINT @message
		FETCH NEXT FROM my_sales_cursor INTO @sid, @total
	END

	FETCH NEXT FROM my_product_cursor INTO @id, @name
	CLOSE my_sales_cursor;
	DEALLOCATE my_sales_cursor;
END

CLOSE my_product_cursor;
DEALLOCATE my_product_cursor;
