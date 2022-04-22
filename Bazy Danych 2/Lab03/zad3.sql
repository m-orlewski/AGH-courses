CREATE TABLE Target(ID int, nazwa varchar(100), cena money
					CONSTRAINT TARGET_PK PRIMARY KEY(ID));

INSERT Target(ID, nazwa, cena) VALUES (1, 'test1', 10000);			
INSERT Target(ID, nazwa, cena) VALUES (2, 'test2', 0);
INSERT Target(ID, nazwa, cena) VALUES (3, 'test3', 200);			
INSERT Target(ID, nazwa, cena) VALUES (4, 'test4', 100);
INSERT Target(ID, nazwa, cena) VALUES (5, 'test5', 0);
INSERT Target(ID, nazwa, cena) VALUES (6, 'test6', 1000);

SELECT ProductID FROM Production.Product
ORDER BY ProductID ASC;

BEGIN TRAN;
MERGE Target as T
USING Production.Product as S
ON (S.ProductID = T.ID)
WHEN NOT MATCHED BY TARGET AND S.ProductID < 320 
	THEN INSERT(ID, nazwa, cena) VALUES(S.ProductID, S.Name, S.ListPrice)
WHEN MATCHED
	THEN UPDATE SET nazwa = S.ProductID, cena = S.ListPrice
WHEN NOT MATCHED BY SOURCE
	THEN DELETE
OUTPUT $action, inserted.*, deleted.*;
ROLLBACK TRAN;

DROP TABLE Target;
