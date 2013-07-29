--[[
Controls: move = w,a,s,d
Change Fog Type:  1 = LINEAR, 2 = EXP, 3 = EXP2
]]

local cena 		= Rscene.new()
local render 	= Rrender.new()
local camera 	= Rcamera.new()
local key 		= Rkeyboard.new()

	render:setCamera(camera)
	camera:setLocY(0.01)
	render:initWindow(800,600,1,600,false)

	render:setScene(cena)

	cena:fogEnable()
	cena:setFogNearFar(1,20)
	cena:setFogDensity(0.2)
	cena:setFogColor(0.1,0.3,0.1)

function Object (self)
	local cobj = Rwavefront.new(self.name) 
	cobj:loadFile(self.model)
	cobj:setLoc(self.loc.x,self.loc.y,self.loc.z)
	if self.scale ~= nil then
		cobj:setScale(self.scale.x,self.scale.y,self.scale.z)
	end
	return cobj
end



local cube2 = Object {
		model = 'import/supermercado.obj',
		loc = {x = 0,y =-6 ,z =1},
		name = 'a',
		force = 12,
		scale = {x=2,y=2,z=2},
		inteligency = 12
		
	}
cena:addWavefront(cube2)

local cube = Object {
		model = 'import/c.obj',
		loc = {x = 0,y =1 ,z =1},
		name = 'b'
	}
	cena:addWavefront(cube)

local cube3 = Object {
		model = 'import/c.obj',
		loc = {x = 0,y =-10 ,z =1},
		name = 'b',
		scale = {x=20, y=0.1,z=20}
	}
	cena:addWavefront(cube3)

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

local run = true
	while  run do
		local time = os.clock();
		if(key:isKeyPressed(Rkeys.K_q)) then
			run = false
		end
		if key:isKeyPressed(Rkeys.K_w) then
			camera:setLocZ(camera:getLocZ()+math.cos(ctheta)*0.1)
			camera:setLocX(camera:getLocX()+math.sin(ctheta)*0.1)
			
			move_camera(0,0) -- update camera position  
		end
		if key:isKeyPressed(Rkeys.K_s) then
			
			camera:setLocZ(camera:getLocZ()-math.cos(ctheta)*0.1)
			camera:setLocX(camera:getLocX()-math.sin(ctheta)*0.1)
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
		if key:isKeyPressed(Rkeys.K_1) then
			cena:setFogType(Rfog.FOG_LINEAR)
		end
		if key:isKeyPressed(Rkeys.K_2) then
			cena:setFogType(Rfog.FOG_EXP)
		end
		if key:isKeyPressed(Rkeys.K_3) then
			cena:setFogType(Rfog.FOG_EXP2)
		end
	    render:render()

	    -- run = false

	end
      

