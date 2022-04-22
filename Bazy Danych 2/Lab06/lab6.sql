USE [master]
GO
CREATE LOGIN [DESKTOP-ONC3PUK\db2labA] FROM WINDOWS WITH DEFAULT_DATABASE=[AdventureWorks2019]
GO
USE [AdventureWorks2019]
GO
CREATE USER [DESKTOP-ONC3PUK\db2labA] FOR LOGIN [DESKTOP-ONC3PUK\db2labA]
GO

USE [AdventureWorks2019]
GO
USE [master]
GO
CREATE LOGIN [db2labC] WITH PASSWORD=N'Passw0rd',
DEFAULT_DATABASE=[AdventureWorks2019], CHECK_EXPIRATION=OFF, CHECK_POLICY=OFF
GO
USE [AdventureWorks2019]
GO
CREATE USER [db2labC] FOR LOGIN [db2labC]
GO

USE [AdventureWorks2019]
GO
ALTER ROLE [DeptA] ADD MEMBER [db2labC]
GO
USE [AdventureWorks2019]
GO
ALTER ROLE [DeptB] ADD MEMBER [db2labC]
GO

USE [AdventureWorks2019]
GO 
GRANT DELETE ON [Vlab].[Employee] 
TO [db2labC] 
GO 
USE [AdventureWorks2019]
GO 
GRANT DELETE ON [Vlab].[Employee] TO [db2labC] 
GO

USE [AdventureWorks2019]
GO
ALTER ROLE [DeptA] ADD MEMBER [db2labA]
GO

-- 1)
USE [AdventureWorks2019]
REVOKE INSERT TO [DeptB] CASCADE
GO

-- 2)
USE [master]
GO
CREATE LOGIN [db2labD] WITH PASSWORD=N'Passw0rd',
DEFAULT_DATABASE=[AdventureWorks2019], CHECK_EXPIRATION=OFF,CHECK_POLICY=OFF
GO
USE [AdventureWorks2019]
GO
CREATE USER [db2labD] FOR LOGIN [db2labD]
GO

-- 3)
USE [AdventureWorks2019]
GO
ALTER ROLE [DeptA] ADD MEMBER [db2labD]
GO
USE [AdventureWorks2019] 
GO
ALTER ROLE [DeptB] ADD MEMBER [db2labD]
GO

-- 4)
USE [AdventureWorks2019]
GO
GRANT INSERT ON [Vlab].[Employee] TO [db2labD] 
GO

--5)
SELECT db2users.[name] As Username
, db2users.[type] AS [User Type]
, db2users.type_desc AS [Type description]
, db2perm.permission_name AS [Permission]
, db2perm.state_desc AS [Permission State]
, db2perm.class_desc Class
, object_name(db2perm.major_id) AS [Object Name]
FROM sys.database_principals db2users
LEFT JOIN
sys.database_permissions db2perm
ON db2perm.grantee_principal_id = db2users.principal_id
WHERE db2users.name IN ('db2labA', 'db2labB', 'db2labC', 'db2labD')
GO

--6)

--INSERT TEST

-- nie dzia³a
EXECUTE AS USER = 'db2labA';
INSERT INTO Vlab.Employee (FirstName, LastName) VALUES ('Michal', 'O')
REVERT;
GO

-- nie dzia³a
EXECUTE AS USER = 'db2labB';
INSERT INTO Vlab.Employee (FirstName, LastName) VALUES ('Michal', 'O')
REVERT;
GO

-- dzia³a
EXECUTE AS USER = 'db2labC';
INSERT INTO Vlab.Employee (FirstName, LastName) VALUES ('Michal', 'O')
REVERT;
GO

-- dzia³a
EXECUTE AS USER = 'db2labD';
INSERT INTO Vlab.Employee (FirstName, LastName) VALUES ('Michal', 'O')
REVERT;
GO

-- UPDATE TEST

-- nie dzia³a
EXECUTE AS USER = 'db2labA';
UPDATE Vlab.Employee SET Salary=100 WHERE LastName='O'
REVERT;
GO

-- nie dzia³a
EXECUTE AS USER = 'db2labB';
UPDATE Vlab.Employee SET Salary=100 WHERE LastName='O'
REVERT;
GO

-- dzia³a
EXECUTE AS USER = 'db2labC';
UPDATE Vlab.Employee SET Salary=100 WHERE LastName='O'
REVERT;
GO

-- dzia³a
EXECUTE AS USER = 'db2labD';
UPDATE Vlab.Employee SET Salary=100 WHERE LastName='O'
REVERT;
GO

-- DELETE TEST

-- nie dzia³a
EXECUTE AS USER = 'db2labA';
DELETE FROM Vlab.Employee WHERE LastName='O';
REVERT;
GO

-- nie dzia³a
EXECUTE AS USER = 'db2labB';
DELETE FROM Vlab.Employee WHERE LastName='O';
REVERT;
GO

EXECUTE AS USER = 'db2labC';
DELETE FROM Vlab.Employee WHERE LastName='O';
REVERT;
GO

-- nie dzia³a
EXECUTE AS USER = 'db2labD';
DELETE FROM Vlab.Employee WHERE LastName='O';
REVERT;
GO