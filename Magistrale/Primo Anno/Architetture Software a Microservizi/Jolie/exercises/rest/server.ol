include "interface.iol"

// Vedi letteralmente qui: https://docs.jolie-lang.org/v1.11.x/language-tools-and-standard-library/rest/index.html

service App {
    execution: sequential

    inputPort Web {
        location: "socket://localhost:8080"
        protocol: http {
            format = "json"
            osc << {
                createNote << {
                    template = "/api/notes"
                    method = "post"
                    statusCodes = 201 // 201 = Created
                    statusCodes.TypeMismatch = 400
                    response.headers -> responseHeaders
                }
                listNotes << {
                    template = "/api/notes"
                    method = "get"
                }
                // viewUser << {
                //     template = "/api/user/{username}"
                //     method = "get"
                //     statusCodes.UserNotFound = 404
                // }
                // updateUser << {
                //     template = "/api/user/{username}"
                //     method = "put"
                //     statusCodes.TypeMismatch = 400
                //     statusCodes.UserNotFound = 404                    
                // }
                // deleteUser << {
                //     template = "/api/user/{username}"
                //     method = "delete"
                //     statusCodes.UserNotFound = 404
                // }
            }
        }
        interfaces: NotesInterface
    }

    init {
        global.notes << {
            a << { id = 1, note = "Test 1" }
            b << { id = 2, note = "Test 2" }
            c << { id = 3, note = "Test 3" }
        }
    }

    main {

        [ createNote( request )( response ) {

            newId = #global.notes
            note << { id = newId, note = request.note }
            global.notes.(note.id) << note
            response << note
        } ]

        // [ createUser( request )( ) {
        //     if( is_defined( global.users.(request.username) ) ) {
        //         throw( UserExists, request.username )
        //     } else {
        //         global.users.(request.username) << request
        //         undef( global.users.(request.username).username )
        //         responseHeaders.Location = "/api/user/" + request.username
        //     }
        // } ]

        // [ viewUser( request )( user ) {
        //     if( is_defined( global.users.(request.username) ) ) {
        //         user << global.users.(request.username)
        //     } else {
        //         throw( UserNotFound, request.username )
        //     }
        // } ]

        [ listNotes( request )( response ) {
            i = 0
            foreach( note : global.notes ) {
                note << global.notes.(note)
                response.notes[i++] << note
            }
        } ]


        // [ deleteUser( request )( ) {
        //     if( is_defined( global.users.(request.username) ) ) {
        //         undef( global.users.(request.username) )
        //     } else {
        //         throw( UserNotFound, request.username )
        //     }
        // } ]
    }
}
