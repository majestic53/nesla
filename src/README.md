# NESLA (NESL-Assembler) Sources

## File layout

* Source files are placed into subdirectories, under `src/`.

|Directory   |Description           |
|:-----------|:---------------------|
|`src/common`|Common source files   |
|`src/`      |Assembler source files|

## Coding style

This project uses the following coding style:

### Enumerations

```c
/*!
 * @enum nesla_xxx_e
 * @brief ...
 */
typedef enum {
    XXX_A = 0,          /*!< Doxygen comment */
    XXX_B,              /*!< Doxygen comment */
    ...
} nesla_xxx_e;
```

### Structures

```c
/*!
 * @struct nesla_xxx_t
 * @brief ...
 */
typedef struct {
    nesla_xxx_e val_0;  /*!< Doxygen comment */
    int val_1;          /*!< Doxygen comment */
    ...
} nesla_xxx_t;
```

### Functions

```c
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

...

/*!
 * @brief ...
 * @param[in,out] arg_0 ...
 * @param[in] arg_1 ...
 * @return ...
 */
int nesla_xxx_yyy(nesla_xxx_t *arg_0, nesla_xxx_e arg_1, ...)
{
    int result = NESL_SUCCESS;

    if(arg_0 == NULL) {
        result = NESLA_FAILURE;
        goto exit;
    }

    ...

exit:
    return result;
}

...

#ifdef __cplusplus
}
#endif /* __cplusplus */
```
