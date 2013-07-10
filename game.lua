local cena 		= Rscene.new()
local render 	= Rrender.new()
local camera 	= Rcamera.new()
local key 		= Rkeyboard.new()

	render:setCamera(camera)
	camera:setLocY(0.01)
	render:initWindow(800,600,0.01,1000,false)

	render:setScene(cena)

local cube2 
for i=0,3,1 do
		cube2 = Rwavefront.new('a')
		cube2:loadFile("import/supermercado.obj")
		cube2:setLocY(-0.01)
		cube2:setLocZ(i*0.2)
		cube2:setScale(0.01,0.01,0.01)
		cube2:setRotY(90)
		cena:addWavefront(cube2)
end

local cube = Rwavefront.new('b')
	cube:loadFile("import/cube.obj")
	--cube:setLocY(-0.01)
	cube:setScale(0.01,0.01,0.01)
	cube:setRotY(90)
	cena:addWavefront(cube)

local lamp = RlightLamp.new('light1')
	cena:addLightLamp(lamp)
	

--#############--##############--
local ctheta,cphi = 0,0
function move_camera(theta,phi) -- 
	local x,y,z

	x = math.sin(ctheta+theta)*math.cos(cphi+phi)+camera:getLocX()
	z = math.cos(ctheta+theta)*math.cos(cphi+phi)+camera:getLocZ()
	y = math.sin(cphi+phi)+camera:getLocY()
	camera:setLocT(x,y,z)

	ctheta = ctheta + theta
	cphi = cphi + phi	
end

local ltheta = 0
function move_light(theta) -- 
	local x,z,y
	y = 0.02
	
	x = math.sin(ltheta+theta)*0.2
	z = math.cos(ltheta+theta)*0.2
	
	lamp:setLocX(x)
	lamp:setLocZ(z)
	lamp:setLocY(y)

	cube:setLocX(x)
	cube:setLocZ(z)
	cube:setLocY(y)

	ltheta = ltheta + theta
		
end

local run = true
	while  run do
		local time = os.clock();
		if(key:isKeyPressed(Rkeys.K_q)) then
			run = false
		end
		if key:isKeyPressed(Rkeys.K_w) then
			camera:setLocZ(camera:getLocZ()+math.cos(ctheta)*0.01)
			camera:setLocX(camera:getLocX()+math.sin(ctheta)*0.01)
			
			move_camera(0,0) -- update camera position  
		end
		if key:isKeyPressed(Rkeys.K_s) then
			
			camera:setLocZ(camera:getLocZ()-math.cos(ctheta)*0.01)
			camera:setLocX(camera:getLocX()-math.sin(ctheta)*0.01)
			move_camera(0,0) -- update camera position 
		end
		if key:isKeyPressed(Rkeys.K_a) then
		   	--camera:setRotY(camera:getRotY()+1)
		   	move_camera(0.04,0)
		end
		if key:isKeyPressed(Rkeys.K_d) then
			--camera:setRotY(camera:getRotY()-1)
			move_camera(-0.04,0)
		end
	    render:render()
	   	move_light(0.01) 
	    print(60/(os.clock()-time)/100)

	    -- run = false

	end
      

