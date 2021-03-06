/**
 * @author qiao / https://github.com/qiao
 * @author mrdoob / http://mrdoob.com
 * @author alteredq / http://alteredqualia.com/
 * @author WestLangley / http://github.com/WestLangley
 */

THREE.OrbitControls = function ( object, domElement ) {

    this.object = object;

    if(domElement === undefined)return;

    //this.domElement = ( domElement !== undefined ) ? domElement : document;

    // API

    this.enabled = true;

    this.center = new THREE.Vector3();

    this.userZoom = true;
    this.userZoomSpeed = 1.0;

    this.userRotate = true;
    this.userRotateSpeed = 1.0;

    this.userPan = true;
    this.userPanSpeed = 2.0;

    this.autoRotate = false;
    this.autoRotateSpeed = 2.0; // 30 seconds per round when fps is 60

    this.minPolarAngle = 0; // radians
    this.maxPolarAngle = Math.PI; // radians

    this.minDistance = 0;
    this.maxDistance = Infinity;

    this.keys = { LEFT: 37, UP: 38, RIGHT: 39, BOTTOM: 40 };

    // internals

    var scope = this;

    var EPS = 0.000001;
    var PIXELS_PER_ROUND = 1800;

    var rotateStart = new THREE.Vector2();
    var rotateEnd = new THREE.Vector2();
    var rotateDelta = new THREE.Vector2();

    var zoomStart = new THREE.Vector2();
    var zoomEnd = new THREE.Vector2();
    var zoomDelta = new THREE.Vector2();

    var phiDelta = 0;
    var thetaDelta = 0;
    var scale = 1;

    var lastPosition = new THREE.Vector3();

    var STATE = { NONE: -1, ROTATE: 0, ZOOM: 1, PAN: 2 };
    var state = STATE.NONE;

    var boolpress;
    var oldx,oldy;
    // events

    var changeEvent = { type: 'change' };


    this.rotateLeft = function ( angle ) {

        if ( angle === undefined ) {

            angle = getAutoRotationAngle();

        }

        thetaDelta -= angle;

    };

    this.rotateRight = function ( angle ) {

        if ( angle === undefined ) {

            angle = getAutoRotationAngle();

        }

        thetaDelta += angle;

    };

    this.rotateUp = function ( angle ) {

        if ( angle === undefined ) {

            angle = getAutoRotationAngle();

        }

        phiDelta -= angle;

    };

    this.rotateDown = function ( angle ) {

        if ( angle === undefined ) {

            angle = getAutoRotationAngle();

        }

        phiDelta += angle;

    };

    this.zoomIn = function ( zoomScale ) {

        if ( zoomScale === undefined ) {

            zoomScale = getZoomScale();

        }

        scale /= zoomScale;

    };

    this.zoomOut = function ( zoomScale ) {

        if ( zoomScale === undefined ) {

            zoomScale = getZoomScale();

        }

        scale *= zoomScale;

    };

    this.pan = function ( distance ) {

        distance.transformDirection( object.matrix );
        distance.multiplyScalar( scope.userPanSpeed );

        object.position.add( distance );
        this.center.add( distance );

    };

    this.update = function () {

        var position = object.position;
        var offset = position.clone().sub( this.center );

        // angle from z-axis around y-axis

        var theta = Math.atan2( offset.x, offset.z );

        // angle from y-axis

        var phi = Math.atan2( Math.sqrt( offset.x * offset.x + offset.z * offset.z ), offset.y );

        if ( this.autoRotate ) {

            this.rotateLeft( getAutoRotationAngle() );

        }

        theta += thetaDelta;
        phi += phiDelta;

        // restrict phi to be between desired limits
        phi = Math.max( this.minPolarAngle, Math.min( this.maxPolarAngle, phi ) );

        // restrict phi to be betwee EPS and PI-EPS
        phi = Math.max( EPS, Math.min( Math.PI - EPS, phi ) );

        var radius = offset.length() * scale;

        // restrict radius to be between desired limits
        radius = Math.max( this.minDistance, Math.min( this.maxDistance, radius ) );

        offset.x = radius * Math.sin( phi ) * Math.sin( theta );
        offset.y = radius * Math.cos( phi );
        offset.z = radius * Math.sin( phi ) * Math.cos( theta );

        position.copy( this.center ).add( offset );

        object.lookAt( this.center );

        thetaDelta = 0;
        phiDelta = 0;
        scale = 1;

        if ( lastPosition.distanceTo( object.position ) > 0 ) {

            this.dispatchEvent( changeEvent );

            lastPosition.copy( object.position );

        }

    };


    function getAutoRotationAngle() {

        return 2 * Math.PI / 60 / 60 * scope.autoRotateSpeed;

    }

    function getZoomScale() {

        return Math.pow( 0.95, scope.userZoomSpeed );

    }

    function onMouseDown( eventx,eventy,button ) {

        if ( scope.enabled === false ) return;
        if ( scope.userRotate === false ) return;

        //event.preventDefault();;

        if(button === 1){
            boolpress = true;
        }

//        if ( button === 1 ) {

//            state = STATE.ROTATE;

//            rotateStart.set( eventx, eventy );

//            console.log("1");

//        } else if ( button === 0 ) {

//            state = STATE.ZOOM;

//            zoomStart.set( eventx, eventy );

//            console.log("0");

//        } else if ( button === 2 ) {

//            state = STATE.PAN;
//            console.log("2");
//        }

        //document.addEventListener( 'mousemove', onMouseMove, false );
        //document.addEventListener( 'mouseup', onMouseUp, false );
        domElement.addEventListener( 'mousemove', onMouseMove, false );
        domElement.addEventListener( 'mouseup', onMouseUp, false );
    }

    function onMouseMove( eventx,eventy ) {
        if(boolpress == true){
            if(eventx > oldx){
                object.position.x += 10;
            }else if(eventx<oldx){
                object.position.x -= 10;
            }else{}
            if(eventy > oldy){
                object.position.y += 10;
            }else if(eventy<oldy){
                object.position.y -= 10;
            }else{}
        }
        oldx = eventx;
        oldy = eventy;
        if ( scope.enabled === false ) return;

        ////event.preventDefault();;

        if ( state === STATE.ROTATE ) {

            rotateEnd.set( eventx, eventy );
            rotateDelta.subVectors( rotateEnd, rotateStart );

            scope.rotateLeft( 2 * Math.PI * rotateDelta.x / PIXELS_PER_ROUND * scope.userRotateSpeed );
            scope.rotateUp( 2 * Math.PI * rotateDelta.y / PIXELS_PER_ROUND * scope.userRotateSpeed );

            rotateStart.copy( rotateEnd );

        } else if ( state === STATE.ZOOM ) {

            zoomEnd.set( eventx, eventy );
            zoomDelta.subVectors( zoomEnd, zoomStart );

            if ( zoomDelta.y > 0 ) {

                scope.zoomIn();

            } else {

                scope.zoomOut();

            }

            zoomStart.copy( zoomEnd );

        } else if ( state === STATE.PAN ) {

            var movementX = event.movementX || event.mozMovementX || event.webkitMovementX || 0;
            var movementY = event.movementY || event.mozMovementY || event.webkitMovementY || 0;

            scope.pan( new THREE.Vector3( - movementX, movementY, 0 ) );

        }

    }

    function onMouseUp( eventx,eventy ) {
        boolpress = false;

        if ( scope.enabled === false ) return;
        if ( scope.userRotate === false ) return;

        //document.removeEventListener( 'mousemove', onMouseMove, false );
        //document.removeEventListener( 'mouseup', onMouseUp, false );

        domElement.removeEventListener( 'mousemove', onMouseMove, false );
        domElement.removeEventListener( 'mouseup', onMouseUp, false );

        state = STATE.NONE;

    }

    function onMouseWheel( eventx,eventy ) {
        console.log("start receive wheel event");

        if ( scope.enabled === false ) return;
        if ( scope.userZoom === false ) return;



        if ( eventy > 0 ) {

            object.position.y += 10;

        } else {

            object.position.y -= 10;

        }
        console.log("end receive wheel event"+eventx+"|"+eventy);
    }

    function onKeyDown( event ) {
        console.log(event.key+","+event);
        if ( scope.enabled === false ) return;
        if ( scope.userPan === false ) return;

        switch ( event.keyCode ) {

            case scope.keys.UP:
                scope.pan( new THREE.Vector3( 0, 1, 0 ) );
                break;
            case scope.keys.BOTTOM:
                scope.pan( new THREE.Vector3( 0, - 1, 0 ) );
                break;
            case scope.keys.LEFT:
                scope.pan( new THREE.Vector3( - 1, 0, 0 ) );
                break;
            case scope.keys.RIGHT:
                scope.pan( new THREE.Vector3( 1, 0, 0 ) );
                break;
        }

    }

    //this.domElement.addEventListener( 'contextmenu', function ( event ) { event.preventDefault();; }, false );
    domElement.addEventListener( 'mousedown', onMouseDown, false );
    domElement.addEventListener( 'mousewheel', onMouseWheel, false );
    domElement.addEventListener( 'DOMMouseScroll', onMouseWheel, false ); // firefox
    domElement.addEventListener( 'keydown', onKeyDown, false );
};

THREE.OrbitControls.prototype = Object.create( THREE.EventDispatcher.prototype );
