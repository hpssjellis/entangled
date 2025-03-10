/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

/**
 * @ingroup common_error
 *
 * @{
 *
 * The following error scheme takes advantage of a 16-bit integer
 * in order to fit in data about an error, its origin and severity
 *
 * ~~~
 * bits devision:
 * 1 -> 6 - actual error code (63 errors)
 * 7 -> 8 - error's severity (4 categories)
 * 9 -> 16 - the module which originated the error (255 different modules)
 *
 * M is the module, S the severity and C the actual error code
 *
 *  16      9        1
 * *--------*--------*
 * |MMMMMMMM|SSCCCCCC|
 * *--------*--------*
 * ~~~
 *
 * @file
 * @brief
 *
 */
#ifndef __COMMON_ERRORS_H__
#define __COMMON_ERRORS_H__

#include <stdio.h>
#include "common/error_strings.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name error severity
 * @{
 */
#define RC_SEVERITY_MASK 0x00C0
#define RC_SEVERITY_SHIFT 6

#define RC_SEVERITY_MINOR (0x0 << RC_SEVERITY_SHIFT)
#define RC_SEVERITY_MODERATE (0x1 << RC_SEVERITY_SHIFT)
#define RC_SEVERITY_MAJOR (0x2 << RC_SEVERITY_SHIFT)
#define RC_SEVERITY_FATAL (0x3 << RC_SEVERITY_SHIFT)
/** @} */

/**
 * @name error module
 * @{
 */
#define RC_MODULE_MASK 0xFF00
#define RC_MODULE_SHIFT 8

#define RC_MODULE_GENERAL (0x01 << RC_MODULE_SHIFT)
#define RC_MODULE_SQLITE3 (0x02 << RC_MODULE_SHIFT)
#define RC_MODULE_NEIGHBOR (0x03 << RC_MODULE_SHIFT)
#define RC_MODULE_CCLIENT (0x04 << RC_MODULE_SHIFT)
#define RC_MODULE_CONSENSUS (0x05 << RC_MODULE_SHIFT)
#define RC_MODULE_CW (0x06 << RC_MODULE_SHIFT)
#define RC_MODULE_EXIT_PROBABILITIES (0x07 << RC_MODULE_SHIFT)
#define RC_MODULE_SNAPSHOT (0x08 << RC_MODULE_SHIFT)
#define RC_MODULE_LEDGER_VALIDATOR (0x09 << RC_MODULE_SHIFT)
#define RC_MODULE_TIP_SELECTOR (0x0A << RC_MODULE_SHIFT)
#define RC_MODULE_TANGLE (0x0B << RC_MODULE_SHIFT)
#define RC_MODULE_UTILS (0x0C << RC_MODULE_SHIFT)
#define RC_MODULE_PROCESSOR (0x0D << RC_MODULE_SHIFT)
#define RC_MODULE_CONF (0x0E << RC_MODULE_SHIFT)
#define RC_MODULE_API (0x0F << RC_MODULE_SHIFT)
#define RC_MODULE_NODE (0x10 << RC_MODULE_SHIFT)
#define RC_MODULE_MAM (0x11 << RC_MODULE_SHIFT)
#define RC_MODULE_HELPERS (0x12 << RC_MODULE_SHIFT)
#define RC_MODULE_CRYPTO (0x13 << RC_MODULE_SHIFT)
#define RC_MODULE_COMMON (0x14 << RC_MODULE_SHIFT)
#define RC_MODULE_HANDLE (0x15 << RC_MODULE_SHIFT)
#define RC_MODULE_NETWORK (0x16 << RC_MODULE_SHIFT)

/** @} */

/* error code module specific */
#define RC_ERRORCODE_MASK 0x003F

/* Macros for Severity of error code */
#define RC_GET_SEVERITY(x) ((x)&RC_SEVERITY_MASK)

/* Macros for module of error code */
#define RC_GET_MODULE(x) ((x)&RC_MODULE_MASK)

/* Macros for Error code module specific */
#define RC_GET_ERRORCODE(x) ((x)&RC_ERRORCODE_MASK)

#define RC_RESOLVE_FORMAT_STR "M=0x%02X, E=0x%02X, S=0x%X (0x%04X)"

#define ERR_BIND_RETURN(expr, e) \
  if (RC_OK != (e = (expr))) {   \
    return e;                    \
  }

#define ERR_BIND_GOTO(expr, e, label) \
  if (RC_OK != (e = (expr))) {        \
    goto label;                       \
  }

#define ERR_GUARD_RETURN(expr, err) \
  if (!(expr)) {                    \
    return err;                     \
  }

#define ERR_GUARD_GOTO(expr, err, e, label) \
  if (!(expr)) {                            \
    e = (err);                              \
    goto label;                             \
  }

/**
 * @brief Error codes
 *
 */
enum retcode_t {
  RC_OK = 0,         /**< Sucess */
  RC_ERROR = 0xFFFF, /**< uninitialized or unknown error */

  // General Module
  RC_NULL_PARAM = 0x01 | RC_MODULE_GENERAL | RC_SEVERITY_MAJOR,
  RC_INVALID_PARAM = 0x02 | RC_MODULE_GENERAL | RC_SEVERITY_MAJOR,
  RC_OOM = 0x03 | RC_MODULE_GENERAL | RC_SEVERITY_MAJOR,
  RC_STILL_RUNNING = 0x04 | RC_MODULE_GENERAL | RC_SEVERITY_MODERATE,

  // SQLite3 Module
  RC_SQLITE3_FAILED_OPEN_DB = 0x01 | RC_MODULE_SQLITE3 | RC_SEVERITY_FATAL,
  RC_SQLITE3_FAILED_INSERT_DB = 0x02 | RC_MODULE_SQLITE3 | RC_SEVERITY_MAJOR,
  RC_SQLITE3_NO_PATH_FOR_DB_SPECIFIED = 0x03 | RC_MODULE_SQLITE3 | RC_SEVERITY_FATAL,
  RC_SQLITE3_FAILED_NOT_IMPLEMENTED = 0x04 | RC_MODULE_SQLITE3 | RC_SEVERITY_MAJOR,
  RC_SQLITE3_FAILED_BINDING = 0x05 | RC_MODULE_SQLITE3 | RC_SEVERITY_MAJOR,
  RC_SQLITE3_FAILED_PREPARED_STATEMENT = 0x06 | RC_MODULE_SQLITE3 | RC_SEVERITY_MAJOR,
  RC_SQLITE3_FAILED_FINALIZE = 0x07 | RC_MODULE_SQLITE3 | RC_SEVERITY_MAJOR,
  RC_SQLITE3_FAILED_STEP = 0x08 | RC_MODULE_SQLITE3 | RC_SEVERITY_MAJOR,
  RC_SQLITE3_FAILED_BEGIN = 0x09 | RC_MODULE_SQLITE3 | RC_SEVERITY_MAJOR,
  RC_SQLITE3_FAILED_END = 0x0A | RC_MODULE_SQLITE3 | RC_SEVERITY_MAJOR,
  RC_SQLITE3_FAILED_ROLLBACK = 0x0B | RC_MODULE_SQLITE3 | RC_SEVERITY_FATAL,
  RC_SQLITE3_FAILED_CONFIG = 0x0C | RC_MODULE_SQLITE3 | RC_SEVERITY_FATAL,
  RC_SQLITE3_FAILED_INITIALIZE = 0x0D | RC_MODULE_SQLITE3 | RC_SEVERITY_FATAL,
  RC_SQLITE3_FAILED_SHUTDOWN = 0x0E | RC_MODULE_SQLITE3 | RC_SEVERITY_FATAL,

  // Neighbor Module
  RC_NEIGHBOR_FAILED_URI_PARSING = 0x01 | RC_MODULE_NEIGHBOR | RC_SEVERITY_MAJOR,
  RC_NEIGHBOR_INVALID_PROTOCOL = 0x02 | RC_MODULE_NEIGHBOR | RC_SEVERITY_MAJOR,
  RC_NEIGHBOR_INVALID_HOST = 0x03 | RC_MODULE_NEIGHBOR | RC_SEVERITY_MAJOR,
  RC_NEIGHBOR_FAILED_SEND = 0x04 | RC_MODULE_NEIGHBOR | RC_SEVERITY_MODERATE,
  RC_NEIGHBOR_FAILED_ENDPOINT_INIT = 0x05 | RC_MODULE_NEIGHBOR | RC_SEVERITY_FATAL,
  RC_NEIGHBOR_FAILED_ENDPOINT_DESTROY = 0x06 | RC_MODULE_NEIGHBOR | RC_SEVERITY_FATAL,
  RC_NEIGHBOR_ALREADY_PAIRED = 0x07 | RC_MODULE_NEIGHBOR | RC_SEVERITY_MODERATE,
  RC_NEIGHBOR_NOT_PAIRED = 0x08 | RC_MODULE_NEIGHBOR | RC_SEVERITY_MODERATE,

  // Cclient Module
  RC_CCLIENT_JSON_CREATE = 0x01 | RC_MODULE_CCLIENT | RC_SEVERITY_FATAL, /**< json create object error, might OOM. */
  RC_CCLIENT_JSON_PARSE =
      0x02 | RC_MODULE_CCLIENT | RC_SEVERITY_MAJOR,                   /**< json parsing error, might the wrong format */
  RC_CCLIENT_HTTP = 0x04 | RC_MODULE_CCLIENT | RC_SEVERITY_MAJOR,     /**< HTTP service error */
  RC_CCLIENT_HTTP_REQ = 0x05 | RC_MODULE_CCLIENT | RC_SEVERITY_MAJOR, /**< HTTP post error */
  RC_CCLIENT_RES_ERROR = 0x07 | RC_MODULE_CCLIENT | RC_SEVERITY_MODERATE,     /**< IRI response error string */
  RC_CCLIENT_JSON_KEY = 0x08 | RC_MODULE_CCLIENT | RC_SEVERITY_MINOR,         /**< JSON key not found */
  RC_CCLIENT_FLEX_TRITS = 0x09 | RC_MODULE_CCLIENT | RC_SEVERITY_MODERATE,    /**< Flex trits converting error */
  RC_CCLIENT_NULL_PTR = 0x0A | RC_MODULE_CCLIENT | RC_SEVERITY_MAJOR,         /**< Null pointer */
  RC_CCLIENT_UNIMPLEMENTED = 0x0B | RC_MODULE_CCLIENT | RC_SEVERITY_MAJOR,    /**< Method unimplemented */
  RC_CCLIENT_INVALID_SECURITY = 0x0C | RC_MODULE_CCLIENT | RC_SEVERITY_MINOR, /**< invalid security level */
  RC_CCLIENT_TX_DESERIALIZE_FAILED =
      0x0E | RC_MODULE_CCLIENT | RC_SEVERITY_MODERATE, /**< transaction object deserialization */
  RC_CCLIENT_INSUFFICIENT_BALANCE = 0x0F | RC_MODULE_CCLIENT | RC_SEVERITY_MINOR, /**< Insufficient balance */
  RC_CCLIENT_POW_FAILED = 0x10 | RC_MODULE_CCLIENT | RC_SEVERITY_MINOR,           /**< PoW failed */
  RC_CCLIENT_INVALID_TRANSFER = 0x11 | RC_MODULE_CCLIENT | RC_SEVERITY_MODERATE,  /**< Invalid transfer object */
  RC_CCLIENT_INVALID_TAIL_HASH = 0x12 | RC_MODULE_CCLIENT | RC_SEVERITY_MAJOR,    /**< Invalid tail hash */
  RC_CCLIENT_INVALID_BUNDLE = 0x13 | RC_MODULE_CCLIENT | RC_SEVERITY_MINOR,       /**< Invalid bundle object */
  RC_CCLIENT_CHECK_BALANCE = 0x14 | RC_MODULE_CCLIENT | RC_SEVERITY_MINOR,        /**< Checking balance value failed */
  RC_CCLIENT_NOT_PROMOTABLE = 0x15 | RC_MODULE_CCLIENT | RC_SEVERITY_MINOR, /**< Unable to promot this transaction */

  // Consensus Module
  RC_CONSENSUS_NOT_IMPLEMENTED = 0x01 | RC_MODULE_CONSENSUS | RC_SEVERITY_MAJOR,

  // Consensus CW Module
  RC_CW_FAILED_IN_DFS_FROM_DB = 0x01 | RC_MODULE_CW | RC_SEVERITY_MAJOR,
  RC_CW_FAILED_IN_LIGHT_DFS = 0x02 | RC_MODULE_CW | RC_SEVERITY_MAJOR,

  // Consensus Exit Probabilities Module
  RC_EXIT_PROBABILITIES_INVALID_ENTRYPOINT = 0x01 | RC_MODULE_EXIT_PROBABILITIES | RC_SEVERITY_MAJOR,
  RC_EXIT_PROBABILITIES_MISSING_RATING = 0x02 | RC_MODULE_EXIT_PROBABILITIES | RC_SEVERITY_MODERATE,
  RC_EXIT_PROBABILITIES_NOT_IMPLEMENTED = 0x03 | RC_MODULE_EXIT_PROBABILITIES | RC_SEVERITY_MAJOR,

  // Snapshot Module
  RC_SNAPSHOT_FILE_NOT_FOUND = 0x01 | RC_MODULE_SNAPSHOT | RC_SEVERITY_FATAL,
  RC_SNAPSHOT_INVALID_FILE = 0x02 | RC_MODULE_SNAPSHOT | RC_SEVERITY_FATAL,
  RC_SNAPSHOT_INVALID_SUPPLY = 0x03 | RC_MODULE_SNAPSHOT | RC_SEVERITY_FATAL,
  RC_SNAPSHOT_INCONSISTENT_SNAPSHOT = 0x04 | RC_MODULE_SNAPSHOT | RC_SEVERITY_FATAL,
  RC_SNAPSHOT_INCONSISTENT_PATCH = 0x05 | RC_MODULE_SNAPSHOT | RC_SEVERITY_MAJOR,
  RC_SNAPSHOT_BALANCE_NOT_FOUND = 0x06 | RC_MODULE_SNAPSHOT | RC_SEVERITY_MODERATE,
  RC_SNAPSHOT_INVALID_SIGNATURE = 0x07 | RC_MODULE_SNAPSHOT | RC_SEVERITY_FATAL,
  RC_SNAPSHOT_FAILED_JSON_PARSING = 0x08 | RC_MODULE_SNAPSHOT | RC_SEVERITY_FATAL,
  RC_SNAPSHOT_SERVICE_NOT_ENOUGH_DEPTH = 0x09 | RC_MODULE_SNAPSHOT | RC_SEVERITY_MODERATE,
  RC_SNAPSHOT_SERVICE_MILESTONE_NOT_LOADED = 0x0A | RC_MODULE_SNAPSHOT | RC_SEVERITY_MODERATE,
  RC_SNAPSHOT_SERVICE_MILESTONE_NOT_SOLID = 0x0B | RC_MODULE_SNAPSHOT | RC_SEVERITY_MODERATE,
  RC_SNAPSHOT_SERVICE_MILESTONE_TOO_OLD = 0x0C | RC_MODULE_SNAPSHOT | RC_SEVERITY_MODERATE,
  RC_SNAPSHOT_METADATA_FAILED_DESERIALIZING = 0x0D | RC_MODULE_SNAPSHOT | RC_SEVERITY_MODERATE,
  RC_SNAPSHOT_METADATA_FAILED_SERIALIZING = 0x0E | RC_MODULE_SNAPSHOT | RC_SEVERITY_MODERATE,
  RC_SNAPSHOT_STATE_DELTA_FAILED_DESERIALIZING = 0x0F | RC_MODULE_SNAPSHOT | RC_SEVERITY_MODERATE,
  RC_SNAPSHOT_MISSING_MILESTONE_TRANSACTION = 0x10 | RC_MODULE_SNAPSHOT | RC_SEVERITY_MODERATE,

  // Ledger Validator Module
  RC_LEDGER_VALIDATOR_INVALID_TRANSACTION = 0x01 | RC_MODULE_LEDGER_VALIDATOR | RC_SEVERITY_MAJOR,
  RC_LEDGER_VALIDATOR_COULD_NOT_LOAD_MILESTONE = 0x02 | RC_MODULE_LEDGER_VALIDATOR | RC_SEVERITY_MAJOR,
  RC_LEDGER_VALIDATOR_INCONSISTENT_DELTA = 0x03 | RC_MODULE_LEDGER_VALIDATOR | RC_SEVERITY_FATAL,
  RC_LEDGER_VALIDATOR_TRANSACTION_NOT_SOLID = 0x04 | RC_MODULE_LEDGER_VALIDATOR | RC_SEVERITY_FATAL,

  // Tip Selector Module
  RC_TIP_SELECTOR_TIPS_NOT_CONSISTENT = 0x01 | RC_MODULE_TIP_SELECTOR | RC_SEVERITY_MODERATE,
  RC_TIP_SELECTOR_REFERENCE_TOO_OLD = 0x02 | RC_MODULE_TIP_SELECTOR | RC_SEVERITY_MODERATE,

  // Tangle Module
  RC_TANGLE_TAIL_NOT_FOUND = 0x01 | RC_MODULE_TANGLE | RC_SEVERITY_MODERATE,
  RC_TANGLE_NOT_A_TAIL = 0x02 | RC_MODULE_TANGLE | RC_SEVERITY_MODERATE,

  // Utils Module
  RC_UTILS_FAILED_REMOVE_FILE = 0x01 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_FAILED_TO_COPY_FILE = 0x02 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_FAILED_TO_OPEN_FILE = 0x03 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_INVALID_SIG_FILE = 0x04 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_INVALID_LOGGER_VERSION = 0x05 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_FAILED_WRITE_FILE = 0x06 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_FAILED_READ_FILE = 0x07 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_FAILED_OPEN_SRC_FILE = 0x08 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_FAILED_OPEN_CREATE_DST_FILE = 0x09 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_FAILED_CLOSE_FILE = 0x0A | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_FILE_DOES_NOT_EXITS = 0x0B | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_SOCKET_TLS_RNG = 0x0C | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_SOCKET_TLS_CA = 0x0D | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_SOCKET_TLS_CLIENT_PEM = 0x0E | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_SOCKET_TLS_CLIENT_PK = 0x0F | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_SOCKET_TLS_CONF = 0x10 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_SOCKET_TLS_AUTHMODE = 0x11 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_SOCKET_CLIENT_AUTH = 0x12 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_SOCKET_TLS_HANDSHAKE = 0x13 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_SOCKET_CONNECT = 0x14 | RC_MODULE_UTILS | RC_SEVERITY_MAJOR,
  RC_UTILS_SOCKET_RECV = 0x15 | RC_MODULE_UTILS | RC_SEVERITY_MINOR,
  RC_UTILS_SOCKET_SEND = 0x16 | RC_MODULE_UTILS | RC_SEVERITY_MINOR,

  // Processor component Module
  RC_PROCESSOR_INVALID_TRANSACTION = 0x01 | RC_MODULE_PROCESSOR | RC_SEVERITY_MODERATE,
  RC_PROCESSOR_INVALID_REQUEST = 0x02 | RC_MODULE_PROCESSOR | RC_SEVERITY_MODERATE,

  // Conf Module
  RC_CONF_INVALID_ARGUMENT = 0x01 | RC_MODULE_CONF | RC_SEVERITY_FATAL,
  RC_CONF_MISSING_ARGUMENT = 0x02 | RC_MODULE_CONF | RC_SEVERITY_FATAL,
  RC_CONF_UNKNOWN_OPTION = 0x03 | RC_MODULE_CONF | RC_SEVERITY_FATAL,
  RC_CONF_PARSER_ERROR = 0x04 | RC_MODULE_CONF | RC_SEVERITY_FATAL,

  // API Module
  RC_API_MAX_GET_TRYTES = 0x01 | RC_MODULE_API | RC_SEVERITY_MODERATE,
  RC_API_FIND_TRANSACTIONS_NO_INPUT = 0x02 | RC_MODULE_API | RC_SEVERITY_MODERATE,
  RC_API_MAX_FIND_TRANSACTIONS = 0x3 | RC_MODULE_API | RC_SEVERITY_MODERATE,
  RC_API_INVALID_DEPTH_INPUT = 0x04 | RC_MODULE_API | RC_SEVERITY_MODERATE,
  RC_API_INVALID_SUBTANGLE_STATUS = 0x05 | RC_MODULE_API | RC_SEVERITY_MODERATE,
  RC_API_TAIL_MISSING = 0x06 | RC_MODULE_API | RC_SEVERITY_MODERATE,
  RC_API_NOT_TAIL = 0x07 | RC_MODULE_API | RC_SEVERITY_MODERATE,
  RC_API_GET_BALANCES_INVALID_THRESHOLD = 0x08 | RC_MODULE_API | RC_SEVERITY_MINOR,
  RC_API_GET_BALANCES_UNKNOWN_TIP = 0x09 | RC_MODULE_API | RC_SEVERITY_MINOR,
  RC_API_GET_BALANCES_INCONSISTENT_TIP = 0x0A | RC_MODULE_API | RC_SEVERITY_MINOR,

  // Node Module
  RC_NODE_SET_PACKET_TRANSACTION_FAILED = 0x01 | RC_MODULE_NODE | RC_SEVERITY_MODERATE,
  RC_NODE_SET_PACKET_REQUEST_FAILED = 0x02 | RC_MODULE_NODE | RC_SEVERITY_MODERATE,

  // MAM Module
  RC_MAM_BUFFER_TOO_SMALL = 0x01 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_INVALID_ARGUMENT = 0x02 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_INVALID_VALUE = 0x03 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_NEGATIVE_VALUE = 0x04 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_INTERNAL_ERROR = 0x05 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_NOT_IMPLEMENTED = 0x06 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_PB3_EOF = 0x07 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_PB3_BAD_ONEOF = 0x08 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_PB3_BAD_OPTIONAL = 0x09 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_PB3_BAD_REPEATED = 0x0A | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_PB3_BAD_MAC = 0x0B | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_PB3_BAD_SIG = 0x0C | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_PB3_BAD_EKEY = 0x0D | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_TRITS_SIZE_T_NOT_SUPPORTED = 0x0E | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_CHANNEL_NOT_FOUND = 0x0F | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_ENDPOINT_NOT_FOUND = 0x10 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_VERSION_NOT_SUPPORTED = 0x11 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_CHANNEL_NOT_TRUSTED = 0x12 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_ENDPOINT_NOT_TRUSTED = 0x13 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_KEYLOAD_IRRELEVANT = 0x14 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_KEYLOAD_OVERLOADED = 0x15 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_BUNDLE_NOT_EMPTY = 0x16 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_BUNDLE_DOES_NOT_CONTAIN_HEADER = 0x17 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_RECV_CTX_NOT_FOUND = 0x18 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_SEND_CTX_NOT_FOUND = 0x19 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_MESSAGE_NOT_FOUND = 0x1A | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_BAD_PACKET_ORD = 0x1B | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_MSS_EXHAUSTED = 0x1C | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_NTRU_POLY_FAILED = 0x1D | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_API_FAILED_CREATE_ENDPOINT = 0x1E | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_API_FAILED_CREATE_CHANNEL = 0x1F | RC_MODULE_MAM | RC_SEVERITY_MODERATE,
  RC_MAM_MSS_NOT_FOUND = 0x20 | RC_MODULE_MAM | RC_SEVERITY_MODERATE,

  // Helpers Module
  RC_HELPERS_POW_INVALID_TX = 0x01 | RC_MODULE_HELPERS | RC_SEVERITY_MODERATE,

  // Crypto Module
  RC_CRYPTO_UNSUPPORTED_SPONGE_TYPE = 0x01 | RC_MODULE_CRYPTO | RC_SEVERITY_MAJOR,

  // Common Module
  RC_COMMON_BUNDLE_SIGN = 0x01 | RC_MODULE_COMMON | RC_SEVERITY_MINOR,

  // Handle Module
  RC_THREAD_CREATE = 0x01 | RC_MODULE_HANDLE | RC_SEVERITY_FATAL,
  RC_THREAD_JOIN = 0x02 | RC_MODULE_HANDLE | RC_SEVERITY_MODERATE,
  RC_COND_INIT = 0x03 | RC_MODULE_HANDLE | RC_SEVERITY_FATAL,
  RC_COND_SIGNAL = 0x04 | RC_MODULE_HANDLE | RC_SEVERITY_FATAL,
  RC_COND_DESTROY = 0x05 | RC_MODULE_HANDLE | RC_SEVERITY_FATAL,
  RC_LOCK_INIT = 0x06 | RC_MODULE_HANDLE | RC_SEVERITY_FATAL,
  RC_LOCK_DESTROY = 0x07 | RC_MODULE_HANDLE | RC_SEVERITY_FATAL,

  // Network Module
  RC_DOMAIN_RESOLUTION = 0x01 | RC_MODULE_NETWORK | RC_SEVERITY_FATAL,
  RC_EVENT_LOOP = 0x02 | RC_MODULE_NETWORK | RC_SEVERITY_FATAL,
  RC_TCP_SERVER_INIT = 0x03 | RC_MODULE_NETWORK | RC_SEVERITY_FATAL,
  RC_INVALID_PACKET = 0x04 | RC_MODULE_NETWORK | RC_SEVERITY_FATAL,
  RC_INVALID_PACKET_TYPE = 0x05 | RC_MODULE_NETWORK | RC_SEVERITY_FATAL,
  RC_FAILED_HANDSHAKE = 0x06 | RC_MODULE_NETWORK | RC_SEVERITY_FATAL,
  RC_WRITE_TCP_FAILED = 0x07 | RC_MODULE_NETWORK | RC_SEVERITY_FATAL,
  RC_ASYNC_INIT_FAILED = 0x08 | RC_MODULE_NETWORK | RC_SEVERITY_FATAL,
  RC_ASYNC_CALL_FAILED = 0x09 | RC_MODULE_NETWORK | RC_SEVERITY_FATAL,
};

typedef enum retcode_t retcode_t;

/**
 * @brief error code to string
 *
 * @param err error code
 * @return string
 */
const char* error_2_string(retcode_t err);

#ifdef __cplusplus
}
#endif

#endif  // __COMMON_ERRORS_H__

/** @} */
