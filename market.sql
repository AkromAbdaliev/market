-- Product
CREATE TABLE product (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL,
    price DECIMAL NOT NULL
);

-- ProductDetail (1-to-1)
CREATE TABLE product_detail (
    id SERIAL PRIMARY KEY,
    product_id INTEGER UNIQUE REFERENCES product(id),
    description TEXT,
    weight DECIMAL
);

-- Customer
CREATE TABLE customer (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL,
    email TEXT UNIQUE NOT NULL
);

-- Purchase (1-to-many)
CREATE TABLE purchase (
    id SERIAL PRIMARY KEY,
    customer_id INTEGER REFERENCES customer(id),
    purchase_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Category
CREATE TABLE category (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL
);

-- ProductCategory (many-to-many)
CREATE TABLE product_category (
    product_id INTEGER REFERENCES product(id),
    category_id INTEGER REFERENCES category(id),
    PRIMARY KEY (product_id, category_id)
);
