use std::ffi::{c_char, c_void, CStr};
use tokenizers::{Encoding, Tokenizer};

#[no_mangle]
pub unsafe extern "C" fn tokenizer_from_pretrained(
    identifier: *const c_char,
    out_ptr: *mut *mut c_void,
) -> i32 {
    if identifier.is_null() || out_ptr.is_null() {
        return -1;
    }

    let c_str = CStr::from_ptr(identifier);
    let model_name = match c_str.to_str() {
        Ok(s) => s,
        Err(_) => return -1,
    };

    match Tokenizer::from_pretrained(model_name, None) {
        Ok(tokenizer) => {
            let boxed_tokenizer = Box::new(tokenizer);
            *out_ptr = Box::into_raw(boxed_tokenizer) as *mut c_void;
            0
        }
        Err(_) => -1,
    }
}

#[no_mangle]
pub unsafe extern "C" fn tokenizer_encode(
    input_ptr: *const c_char,
    tokenizer_ptr: *const c_void,
    out_ptr: *mut *mut c_void,
) -> i32 {
    if input_ptr.is_null() || out_ptr.is_null() || tokenizer_ptr.is_null() {
        return -1;
    }

    let c_str = CStr::from_ptr(input_ptr);
    let input = match c_str.to_str() {
        Ok(s) => s,
        Err(_) => return -1,
    };

    let tokenizer: &mut Tokenizer = unsafe { &mut *(tokenizer_ptr as *mut Tokenizer) };
    match tokenizer.encode(input, false) {
        Ok(encoding) => {
            let boxed_encoding = Box::new(encoding);
            *out_ptr = Box::into_raw(boxed_encoding) as *mut c_void;
            0
        }
        Err(_) => -1,
    }
}

#[no_mangle]
pub unsafe extern "C" fn tokenizer_encoding_get_ids(
    encoding_ptr: *mut c_void,
    out_ptr: *mut *const u32,
    out_len: *mut usize,
) -> i32 {
    if encoding_ptr.is_null() || out_ptr.is_null() || out_len.is_null() {
        return -1;
    }

    let encoding: &mut Encoding = unsafe { &mut *(encoding_ptr as *mut Encoding) };
    *out_ptr = encoding.get_ids().as_ptr();
    *out_len = encoding.get_ids().len();
    0
}

#[no_mangle]
pub unsafe extern "C" fn tokenizer_encoding_free(ptr: *mut c_void) {
    if !ptr.is_null() {
        let _ = Box::from_raw(ptr as *mut Encoding);
    }
}

#[no_mangle]
pub unsafe extern "C" fn tokenizer_free(ptr: *mut c_void) {
    if !ptr.is_null() {
        let _ = Box::from_raw(ptr as *mut Tokenizer);
    }
}
