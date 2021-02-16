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
import {Gauge} from '../../ui/Gauge.js';

export class DivingPlane extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		this.keyDown = this.keyDown.bind(this);
		
		App.registerComponent("diving_plane", this);
	}
	
	componentDidMount() {
		document.addEventListener('keydown', this.keyDown);
		document.addEventListener('keyup', this.keyUp);
	}
	
	componentWillUnmount() {
		document.removeEventListener('keydown', this.keyDown);
		document.addEventListener('keyup', this.keyUp);
	}
	
	keyDown(e) {
		if(e.key=="+")
			App.api.command({component: "diving_plane", action: "rate_plus"});
		if(e.key=="-")
			App.api.command({component: "diving_plane", action: "rate_minus"});
		if(e.key=="9")
			App.api.command({component: "diving_plane", action: "surface"});
		/*if(e.key=="6")
			App.api.command({component: "diving_plane", action: "neutral"});*/
		if(e.key=="3")
			App.api.command({component: "diving_plane", action: "dive"});
	}
	
	render() {
		if(this.state.diving_plane===undefined)
			return null;
		
		return (
			<div className="DivingPlane container">
				<div className="legend">Diving plane</div>
				<Gauge current={this.state.diving_plane.tilt} min="-15" max="15" min_angle="-120" max_angle="-60" display={Math.round(this.state.diving_plane.tilt)} />
			</div>
		);
	}
}
