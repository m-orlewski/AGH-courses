WITH FirstCTE
(
    CustomerID,
    TerritoryID,
    NoOrder
)
AS
(
    SELECT CustomerID, TerritoryID, COUNT(SubTotal) FROM Sales.SalesOrderHeader
    GROUP BY TerritoryID, CustomerID    
),
SecondCTE
(
    LastName,
    Name,
    NoOrder
) 
AS
(
    SELECT LastName, Name, NoOrder FROM FirstCTE
    JOIN Sales.SalesTerritory ON Sales.SalesTerritory.TerritoryID = FirstCTE.TerritoryID
    JOIN Sales.Customer ON Sales.Customer.CustomerID = FirstCTE.CustomerID
    JOIN Person.Person ON Sales.Customer.PersonID = Person.Person.BusinessEntityID
)
SELECT *, TopCustomer = DENSE_RANK() OVER (ORDER BY NoOrder DESC) FROM SecondCTE;