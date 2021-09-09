-- From https://www.w3resource.com/mysql-exercises/northwind/products-table-exercises/index.php#PracticeOnline

-- 1. Write a query to get Product name and quantity/unit.

SELECT ProductName, QuantityPerUnit
FROM Products;

-- 2. Write a query to get current Product list (Product ID and name).

SELECT ProductID, ProductName
FROM Products
WHERE Discontinued = FALSE
ORDER BY ProductName;

-- 3. Write a query to get discontinued Product list (Product ID and name).

SELECT ProductID, ProductName
FROM Products
WHERE Discontinued = TRUE
ORDER BY ProductName;

-- 4. Write a query to get most expense and least expensive Product list (name and unit price).

SELECT ProductName, Price
FROM Products
WHERE Price = (SELECT MAX(Price) FROM Products)
OR Price = (SELECT MIN(Price) FROM Products);

-- 5. Write a query to get Product list (id, name, unit price) where current products cost less than $20.

SELECT ProductID, ProductName, Price
FROM Products
WHERE Price < 20 AND Discontinued = FALSE
ORDER BY Price DESC;

-- 6. Write a query to get Product list (id, name, unit price) where products cost between $15 and $25.

SELECT ProductID, ProductName, Price
FROM Products
WHERE Price BETWEEN 15 AND 25
ORDER BY Price DESC;

-- 7. Write a query to get Product list (name, unit price) of above average price.

SELECT ProductID, ProductName, Price
FROM Products
WHERE Price >
(SELECT AVG(Price) FROM Products)
ORDER BY Price DESC;

-- 8. Write a query to get Product list (name, unit price) of ten most expensive products.

SELECT DISTINCT ProductID, ProductName, Price
FROM Products
ORDER BY Price DESC
LIMIT 10;

-- 9. Write a query to count current and discontinued products.

SELECT COUNT(ProductID)
FROM Products
GROUP BY Discountinued;

-- 10. Write a query to get Product list (name, units on order , units in stock) of stock is less than the quantity on order.

SELECT ProductName, UnitsOnOrder, UnitsInStock
FROM Products
WHERE UnitsInStock < UnitsOnOrder;
