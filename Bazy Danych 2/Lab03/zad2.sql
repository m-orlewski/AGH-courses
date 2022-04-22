SELECT [ShiftName], [Production], [Information Services], [Marketing], [Research and Development]
FROM
(
	SELECT EDH.DepartmentID AS [DepID], D.Name AS [DepName], S.Name AS [ShiftName]
	FROM HumanResources.EmployeeDepartmentHistory EDH
	LEFT JOIN HumanResources.Shift S ON S.ShiftID = EDH.ShiftID
	LEFT JOIN HumanResources.Department D ON D.DepartmentID = EDH.DepartmentID
) DataTableAlias
PIVOT
(
	COUNT(DepID)
	FOR DepName
	IN
	(
		[Production], [Information Services], [Marketing], [Research and Development]
	)
) PivotTableAlias

SELECT
	S.Name AS [ShiftName],
	SUM(CASE
			WHEN D.Name = 'Production' THEN 1
			ELSE 0
		END) AS [Production],
	SUM(CASE
			WHEN D.Name = 'Information Services' THEN 1
			ELSE 0
		END) AS [Information Services],
	SUM(CASE
			WHEN D.Name = 'Marketing' THEN 1
			ELSE 0
		END) AS [Marketing],
	SUM(CASE
			WHEN D.Name = 'Research and Development' THEN 1
			ELSE 0
		END) AS [Research and Development]
FROM HumanResources.EmployeeDepartmentHistory EDH
LEFT JOIN HumanResources.Shift S ON S.ShiftID = EDH.ShiftID
LEFT JOIN HumanResources.Department D ON D.DepartmentID = EDH.DepartmentID
GROUP BY S.Name;
