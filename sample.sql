#!/bin/ksh


sql<

SELECT
    c.customer_id,
    c.customer_name,
    c.email,
    o.order_id,
    o.order_date,
    o.total_amount
FROM
    Customers c
LEFT JOIN
    (SELECT
        order_id,
        customer_id,
        order_date,
        total_amount,
        ROW_NUMBER() OVER (PARTITION BY customer_id ORDER BY order_date DESC) as rn
    FROM
        Orders) o ON c.customer_id = o.customer_id AND o.rn = 1;
