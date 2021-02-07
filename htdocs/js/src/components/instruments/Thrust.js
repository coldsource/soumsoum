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

export class Thrust extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		this.keyDown = this.keyDown.bind(this);
		this.keyUp = this.keyUp.bind(this);
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
			App.api.command({component: this.props.name, action: "rate_plus"});
		if(e.key=="-")
			App.api.command({component: this.props.name, action: "rate_minus"});
		if(e.key=="2")
			App.api.command({component: this.props.name, action: "angle_x_minus"});
		if(e.key=="8")
			App.api.command({component: this.props.name, action: "angle_x_plus"});
	}
	
	keyUp(e) {
		App.api.command({component: this.props.name, action: "angle_x_neutral"});
	}
	
	render() {
		let fill = ''+Math.round(this.props.data.volume * 1000);
		let len = (''+(this.props.data.capacity*1000)).length;
		fill = fill.padStart(5, '0');
		
		return (
			<div className="Thrust">
				<h2>{this.props.name}</h2>
				<Gauge current={this.props.data.targeted_rate} max={1} />
				<Gauge current={this.props.data.rate} max={1} />
			</div>
		);
	}
}
