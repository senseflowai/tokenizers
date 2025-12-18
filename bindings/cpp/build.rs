extern crate cbindgen;

use std::env;
use std::path::{Path, PathBuf};
use cbindgen::{Builder};

fn main() {
    let out_dir = env::var("CARGO_OUTPUT_HEADER_DIR").unwrap();
    let output_header_file = PathBuf::from(out_dir).join("tokenizers.h");
    let crate_env = env::var("CARGO_MANIFEST_DIR").unwrap();
    let crate_path = Path::new(&crate_env);
    let config: cbindgen::Config = cbindgen::Config::from_file("cbindgen.toml").unwrap_or_default();
    Builder::new().with_crate(crate_path.to_str().unwrap())
        .with_config(config)
        .generate()
        .expect("Cannot generate header file!")
        .write_to_file(output_header_file);
}