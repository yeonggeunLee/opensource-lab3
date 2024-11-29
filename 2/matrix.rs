use std::io;

fn main() {
    let mut rows = String::new();
    let mut cols = String::new();

    println!("Enter the number of rows: ");
    io::stdin().read_line(&mut rows).expect("Failed to read line");
    let rows: usize = rows.trim().parse().expect("Please enter a valid positive integer");

    println!("Enter the number of columns: ");
    io::stdin().read_line(&mut cols).expect("Failed to read line");
    let cols: usize = cols.trim().parse().expect("Please enter a valid positive integer");

    if rows == 0 || cols == 0 {
        println!("Invalid matrix size. Rows and columns must be greater than 0.");
        return;
    }

    let matrix_a = input_matrix(rows, cols, "A");
    let matrix_b = input_matrix(rows, cols, "B");
    let matrix_c = add_matrices(&matrix_a, &matrix_b);

    println!("Resulting matrix C:");
    for row in matrix_c {
        println!("{}", row.iter().map(|x| x.to_string()).collect::<Vec<String>>().join(" "));
    }
}

fn input_matrix(rows: usize, cols: usize, name: &str) -> Vec<Vec<i32>> {
    let mut matrix = vec![vec![0; cols]; rows];
    println!("Enter elements of matrix {}:", name);
    for i in 0..rows {
        let mut input = String::new();
        io::stdin().read_line(&mut input).expect("Failed to read line");
        let elements: Vec<i32> = input.split_whitespace()
            .map(|s| s.trim().parse().expect("Invalid input, please enter integers"))
            .collect();
        if elements.len() != cols {
            println!("Invalid number of elements in row. Expected: {} elements.", cols);
            std::process::exit(1);
        }
        matrix[i] = elements;
    }
    matrix
}

fn add_matrices(a: &[Vec<i32>], b: &[Vec<i32>]) -> Vec<Vec<i32>> {
    let rows = a.len();
    let cols = a[0].len();
    let mut result = vec![vec![0; cols]; rows];
    for i in 0..rows {
        for j in 0..cols {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    result
}

