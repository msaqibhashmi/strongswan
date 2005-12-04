/**
 * @file identification.h
 *
 * @brief Interface of identification_t.
 *
 */

/*
 * Copyright (C) 2005 Jan Hutter, Martin Willi
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */


#ifndef _IDENTIFICATION_H_
#define _IDENTIFICATION_H_


#include "types.h"

typedef enum id_type_t id_type_t;

/**
 * ID Types of a ID payload.
 * 
 * @ingroup utils
 */
enum id_type_t {
	/**
	 * ID data is a single four (4) octet IPv4 address.
	 */
	ID_IPV4_ADDR = 1,

	/**
	 * ID data is a fully-qualified domain name string.
	 * An example of a ID_FQDN is, "example.com".
	 * The string MUST not contain any terminators (e.g., NULL, CR, etc.).
	 */
	ID_FQDN = 2,
	
	/**
	 * ID data is a fully-qualified RFC822 email address string, An example of
	 * a ID_RFC822_ADDR is, "jsmith@example.com".  The string MUST
	 * not contain any terminators.
	 */
	ID_RFC822_ADDR = 3,
	
	/**
	 * ID data is a single sixteen (16) octet IPv6 address.
	 */
	ID_IPV6_ADDR = 5,
	
	/**
	 * ID data is the binary DER encoding of an ASN.1 X.500 Distinguished Name
     * [X.501].
     */
	ID_DER_ASN1_DN = 9,
	
	/**
	 * ID data is the binary DER encoding of an ASN.1 X.500 GeneralName
     * [X.509].
     */
	ID_DER_ASN1_GN = 10,
	
	/**
	 * ID data is an opaque octet stream which may be used to pass vendor-
     * specific information necessary to do certain proprietary
     * types of identification.
     */
	ID_KEY_ID = 11
};

extern mapping_t id_type_m[];

typedef struct identification_t identification_t;

/**
 * @brief Generic identification, such as used in ID payload.
 * 
 * The following types are possible:
 * 
 * - ID_IPV4_ADDR 
 * - ID_FQDN (not implemented)
 * - ID_RFC822_ADDR  (not implemented)
 * - ID_IPV6_ADDR (not implemented)
 * - ID_DER_ASN1_DN  (not implemented)
 * - ID_DER_ASN1_GN (not implemented)
 * - ID_KEY_ID (not implemented)
 *
 * @ingroup utils
 */
struct identification_t {
	
	/**
	 * @brief Get the encoding of this id, to send over
	 * the network.
	 * 
	 * @warning Result points to internal data, do NOT free!
	 * 
	 * @param this		the identification_t_object
	 * @return 			a chunk containing the encoded bytes
	 */
	chunk_t (*get_encoding) (identification_t *this);
	
	/**
	 * @brief Get the type of this identification.
	 * 
	 * @param this		the identification_t_object
	 * @return 			id_type_t
	 */
	id_type_t (*get_type) (identification_t *this);
	
	/**
	 * @brief Get a string representation of this id.
	 * 
	 * @warning Result points to internal data, do NOT free!
	 * 
	 * @param this		the identification_t_object
	 * @return 			string
	 */
	char *(*get_string) (identification_t *this);
	
	/**
	 * @brief Check if two identification_t objects are equal.
	 * 
	 * @param this		the identification_t_object
	 * @param other		other identification_t_object
	 * @return 			string
	 */
	bool (*equals) (identification_t *this,identification_t *other);


	/**
	 * @brief Destroys a identification_t object.
	 *
	 * @param this 				identification_t object
	 */
	void (*destroy) (identification_t *this);
};

/**
 * @brief Creates an identification_t object from a string.
 * 
 * @param type		type of this id, such as ID_IPV4_ADDR or ID_RFC822_ADDR
 * @param string	input string, which will be converted
 * @return
 * 					- created identification_t object, or
 * 					- NULL if type not supported.
 * 
 * @ingroup utils
 */
identification_t * identification_create_from_string(id_type_t type, char *string);


/**
 * @brief Creates an identification_t object from an encoded chunk.
 * 
 * @param type		type of this id, such as ID_IPV4_ADDR or ID_RFC822_ADDR
 * @param encoded	encoded bytes, such as from identification_t.get_encoding
 * @return			created identification_t object
 * 
 * @ingroup utils
 */
identification_t * identification_create_from_encoding(id_type_t type, chunk_t encoded);


#endif //_IDENTIFICATION_H_
