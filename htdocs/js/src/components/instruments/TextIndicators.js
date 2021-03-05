 /*
  * This file is part of evQueue
  *
  * evQueue is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * evQueue is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with evQueue. If not, see <http://www.gnu.org/licenses/>.
  *
  * Author: Thibault Kummer
  */

'use strict';

import {App} from '../base/App.js';
import {TextDisplay} from '../../ui/TextDisplay.js';

export class TextIndicators extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {};
		
		App.registerComponent("moving_body", this);
		App.registerComponent("air_controller", this);
		App.registerComponent("ballast", this);
	}
	
	render() {
		if(this.state.moving_body===undefined || this.state.air_controller===undefined || this.state.ballast===undefined)
			return null;
		
		return (
			<div className="TextIndicators container">
				<TextDisplay text="SURFACE" type="notice" status={this.state.moving_body.position.z>-8?"on":"off"} />
				<br /><TextDisplay text="IMMERSION" type="notice" status={this.state.moving_body.position.z<=-8?"on":"off"} />
				<br /><TextDisplay text="DEPTH" type="warning" status={this.state.moving_body.position.z<-300?"on":"off"} />
				<br /><TextDisplay text="AIR PRESSURE" type="warning" status={this.state.air_controller.main_tank.air.pressure>305 || this.state.air_controller.main_tank.air.pressure<50?"on":"off"} />
				<br /><TextDisplay text="BALLAST FULL" type="notice" status={this.state.ballast.fill==1?"on":"off"} />
				<br /><TextDisplay text="BALLAST OPEN" type="warning" status={this.state.ballast.opened?"on":"off"} />
			</div>
		);
	}
}
