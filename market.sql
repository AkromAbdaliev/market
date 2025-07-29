-- One-to-One: Each Product has one ProductDetail
CREATE TABLE product_details (
    id SERIAL PRIMARY KEY,
    description TEXT,
    weight DECIMAL
);

CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL,
    price DECIMAL NOT NULL,
    detail_id INTEGER UNIQUE REFERENCES product_details(id)
);

-- One-to-Many: A User has many Orders
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL,
    email TEXT UNIQUE NOT NULL
);

CREATE TABLE orders (
    id SERIAL PRIMARY KEY,
    user_id INTEGER REFERENCES users(id),
    order_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Many-to-Many: Products belong to many Categories
CREATE TABLE categories (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL
);

CREATE TABLE product_categories (
    product_id INTEGER REFERENCES products(id),
    category_id INTEGER REFERENCES categories(id),
    PRIMARY KEY (product_id, category_id)
);

--                 Inserted Datas

-- Insert into product_details first ----------------------------------------
INSERT INTO product_details (description, weight)
VALUES 
  ('High-quality coffee beans', 0.5),   -- id = 1
  ('Premium dark chocolate bar', 0.2);  -- id = 2

-- Then insert products referencing those details
INSERT INTO products (name, price, detail_id)
VALUES 
  ('Coffee Beans', 15.99, 1),
  ('Chocolate Bar', 4.50, 2);


-- Insert users -------------------------------------------------------------
INSERT INTO users (name, email)
VALUES 
  ('Alice', 'alice@example.com'),     -- id = 1
  ('Bob', 'bob@example.com');         -- id = 2

-- Insert orders for users
INSERT INTO orders (user_id)
VALUES 
  (1),  -- Alice's first order
  (1),  -- Alice's second order
  (2);  -- Bob's only order


-- Insert categories  -------------------------------------------------------
INSERT INTO categories (name)
VALUES 
  ('Beverages'),   -- id = 1
  ('Snacks'),      -- id = 2
  ('Organic');     -- id = 3

-- Insert product-category relations
-- Assuming Coffee Beans = product_id 1, Chocolate Bar = product_id 2
INSERT INTO product_categories (product_id, category_id)
VALUES 
  (1, 1),  -- Coffee Beans → Beverages
  (1, 3),  -- Coffee Beans → Organic
  (2, 2);  -- Chocolate Bar → Snacks

 












