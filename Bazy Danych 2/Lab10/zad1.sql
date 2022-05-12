USE AdventureWorks2008
GO


-- 1)
SELECT Demographics.value('declare default element namespace
"http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/IndividualSurvey";
(/IndividualSurvey/YearlyIncome)[1]', 'varchar(250)') AS 'Yearly Income'
FROM Person.Person;
