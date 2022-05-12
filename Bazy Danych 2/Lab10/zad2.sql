USE AdventureWorks2008
GO

-- 2)
SELECT FirstName, LastName, Demographics.value('declare default element namespace
"http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/IndividualSurvey";
(/IndividualSurvey/TotalChildren)[1]','Integer')
-
Demographics.value('declare default element namespace
"http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/IndividualSurvey";
(/IndividualSurvey/NumberChildrenAtHome)[1]','Integer')
AS 'Result'
FROM Person.Person
WHERE
Demographics.value('declare default element namespace
"http://schemas.microsoft.com/sqlserver/2004/07/adventure-works/IndividualSurvey";
(/IndividualSurvey/TotalChildren)[1]','Integer') > 0
ORDER BY 3 DESC;
